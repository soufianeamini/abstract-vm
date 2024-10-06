#!/usr/bin/env python3

import os
from pathlib import Path
from threading import Thread

root_path = Path(os.curdir).resolve()
deps_dir = root_path / "deps"
install_dir = root_path / "external-libs"
cmake_command = f"cmake -DFMT_TEST=OFF -DJSON_BuildTests=OFF -DCMAKE_INSTALL_PREFIX:PATH={install_dir} .."

# print(root_path)
# print(deps_dir)
# print(install_dir)
# print(cmake_command)

def download_cmake_lib(url, tag, name: str):
    target_dir = deps_dir / name

    if target_dir.exists():
        print(f"{target_dir} already exists. Skipping git clone..")
    else:
        os.system(f"git clone --depth 1 --branch {tag} {url} {target_dir}")

    tasks = [
        lambda : os.system(f"mkdir -p {target_dir / 'build'}"),
        lambda : os.chdir(target_dir / "build"),
        lambda : os.system(cmake_command),
        lambda : os.system("make install"),
    ]

    i = 0
    for task in tasks:
        if task():
            print(f"Error executing task id: {i}. Aborting...")
            return
        i += 1

libs = [
    lambda : download_cmake_lib(url="git@github.com:nlohmann/json.git", tag="v3.11.3", name="json"),
    lambda : download_cmake_lib(url="git@github.com:fmtlib/fmt.git", tag="11.0.2", name="fmt"),
]

handles: list[Thread] = []

for lib in libs:
    thread = Thread(target=lib)
    thread.start()
    handles.append(thread)

for handle in handles:
    handle.join()
