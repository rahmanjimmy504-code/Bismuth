#!/usr/bin/env python3
"""Compile production ground ancestry classification against a small fake Cocos API."""
from pathlib import Path
import subprocess
import tempfile

root = Path(__file__).resolve().parents[1]
def source(name):
    return "\n".join(
        line for line in (root / name).read_text().splitlines()
        if not line.startswith(("#include", "#pragma once"))
    )

code = "\n".join([
    "#define BISMUTH_GLES_BACKEND",
    '#include "mobile_ground_fixture.hpp"',
    source("src/renderer/mobile/GroundOwnership.hpp"),
    (root / "tests/mobile_ground_cases.cpp").read_text(),
])
with tempfile.TemporaryDirectory(prefix="bismuth-ground-tests-") as directory:
    path = Path(directory)
    (path / "test.cpp").write_text(code)
    subprocess.run([
        "g++", "-std=c++23", "-O1", "-g", "-Wall", "-Wextra",
        "-fsanitize=address,undefined", "-fno-omit-frame-pointer",
        "-I", str(root / "tests"), str(path / "test.cpp"),
        "-o", str(path / "test"),
    ], check=True)
    subprocess.run([str(path / "test")], check=True)
