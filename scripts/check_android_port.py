#!/usr/bin/env python3
"""Cheap invariants for the unofficial Android64 GLES2 port (not a native build)."""
from __future__ import annotations

import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
manifest = json.loads((ROOT / "mod.json").read_text())
cmake = (ROOT / "CMakeLists.txt").read_text()
workflow = (ROOT / ".github/workflows/android64.yml").read_text()

assert manifest["gd"].get("android") == "2.2081", "manifest must target Android GD 2.2081"
assert "win" not in manifest["gd"], "this package must not claim Windows support"
assert manifest["id"] == "community.bismuth-android", "keep the unofficial port ID distinct"
assert "BISMUTH_GLES_BACKEND=1" in cmake, "mobile GLES backend macro is not enabled"
assert "GLESv2" in cmake, "Android GLESv2 must be linked"
assert "target: Android64" in workflow, "CI must build the Android64 target"
assert (ROOT / "LICENSE.md").is_file(), "upstream license must be included"
license_text = (ROOT / "LICENSE.md").read_text()
assert "GNU General Public License" in license_text
assert "LEVEL GENERATION OR MODIFICATION USING" in license_text

# These translation units are the active GLES backend. Keep desktop-only entry
# points out of it; the project must use GLES shaders and CPU-side state uploads.
mobile_root = ROOT / "src/renderer/mobile"
for path in mobile_root.rglob("*"):
    if not path.is_file() or path.suffix not in {".cpp", ".hpp", ".h"}:
        continue
    text = path.read_text(errors="ignore")
    for forbidden in (
        "wglGetProcAddress",
        "glDispatchCompute",
        "glMultiDrawArraysIndirect",
        "glMultiDrawElementsIndirect",
        "GL_SHADER_STORAGE_BUFFER",
        "#version 460",
    ):
        assert forbidden not in text, f"desktop-only symbol {forbidden} in {path.relative_to(ROOT)}"

for shader in (ROOT / "resources/shaders").glob("*.vert"):
    text = shader.read_text()
    assert "#version 460" not in text, f"desktop GLSL version in {shader.name}"

assert not any("GEODE_IS_IOS" in p.read_text(errors="ignore") for p in (ROOT / "src").rglob("*.cpp")), \
    "mobile code must use the explicit BISMUTH_GLES_BACKEND guard, not an iOS-only build guard"

print("PASS: Android 2.2081 / Android64 manifest, GLES2 backend, source license, and mobile renderer guards")
print("NOTE: this check does not compile the NDK target or prove phone rendering/performance")
