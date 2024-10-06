#[cfg(test)]
mod test {
    use std::error::Error;

    type TestResult<T> = Result<T, Box<dyn Error>>;
    mod avm_bin {
        use std::{
            fs,
            io::Write,
            process::{Command, ExitStatus, Output, Stdio},
        };

        use super::TestResult;

        fn execute_program(command: &str, args: Vec<&str>) -> TestResult<Output> {
            Ok(Command::new(command).args(args).output()?)
        }

        fn execute_program_with_input(
            command: &str,
            args: Vec<&str>,
            input: &[u8],
        ) -> TestResult<Output> {
            let mut child = Command::new(command)
                .args(args)
                .stdin(Stdio::piped())
                .stdout(Stdio::piped())
                .spawn()?;
            let mut stdin = child.stdin.take().unwrap();
            stdin.write_all(input)?;

            Ok(child.wait_with_output()?)
        }

        #[test]
        fn test_example_from_input() -> TestResult<()> {
            let input = fs::read("tests/example.avm.input")?;
            let output = execute_program_with_input("./avm", vec![], &input)?;
            let expected = fs::read_to_string("tests/example.avm.output")?;
            let actual = String::from_utf8(output.stdout)?;

            assert_eq!(expected, actual);
            assert_eq!(output.status, ExitStatus::default());
            Ok(())
        }

        #[test]
        fn test_example() -> TestResult<()> {
            let output = execute_program("./avm", vec!["tests/example.avm"])?;
            let expected = fs::read_to_string("tests/example.avm.output")?;
            let actual = String::from_utf8(output.stdout)?;

            assert_eq!(expected, actual);

            // In order to add an error message to a test
            // assert!(actual.contains("42"), "{actual}");

            assert_eq!(output.status, ExitStatus::default());
            Ok(())
        }
    }
}
