#!/usr/bin/env python3

import os
from pathlib import Path
from threading import Thread

root_path = Path(os.curdir).resolve()
deps_dir = root_path / "deps"
install_dir = root_path / "external-libs"
cmake_command = f"cmake -DCMAKE_INSTALL_PREFIX:PATH={install_dir} .."

print(root_path)
print(deps_dir)
print(install_dir)
print(cmake_command)

# TODO: check for existence before installing a lib
# TODO: handle error at every process invocation

def download_lib(url, tag, name):
    target_dir = deps_dir / name

    os.system(f"git clone --depth 1 --branch {tag} {url} {target_dir}")
    os.system(f"mkdir {target_dir / 'build'}")
    os.chdir(target_dir / "build")
    os.system(cmake_command)
    os.system("make install")

# TODO: generalize the concurrent code by gathering lambdas in an array and starting and joining threads by collecting them through another array

t1 = Thread(target=lambda : download_lib(url="git@github.com:nlohmann/json.git", tag="v3.11.3", name="json"))
t2 = Thread(target=lambda : download_lib(url="git@github.com:fmtlib/fmt.git", tag="11.0.2", name="fmt"))

t1.start()
t2.start()

t1.join()
t2.join()
#
# download_lib(url="git@github.com:nlohmann/json.git", tag="v3.11.3", name="json")
# download_lib(url="git@github.com:fmtlib/fmt.git", tag="11.0.2", name="fmt")
