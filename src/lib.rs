#[cfg(test)]
mod test {
    use std::error::Error;

    type TestResult<T> = Result<T, Box<dyn Error>>;
    mod avm_bin {
        use std::{fs, process::{Command, ExitStatus, Output}};

        use super::TestResult;

        fn execute_program(command: &str, args: Vec<&str>) -> TestResult<Output> {
            Ok(Command::new(command).args(args).output()?)
        }

        #[test]
        fn test_addition() -> TestResult<()> {
            let output = execute_program("./avm", vec!["tests/example.avm"])?;
            let expected = fs::read_to_string("tests/example.avm.output")?;
            let stdout = output.stdout;
            let actual = String::from_utf8(stdout)?;

            assert_eq!(expected, actual);

            // In order to add an error message to a test
            // assert!(actual.contains("42"), "{actual}");

            assert_eq!(output.status, ExitStatus::default());
            Ok(())
        }
    }
}
