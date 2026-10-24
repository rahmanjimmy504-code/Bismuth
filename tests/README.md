# Mobile GLES renderer regression checks

Run from the repository root with Python 3, a C++23-capable GCC, and a Mesa GLES
runtime (`libEGL`):

```sh
python3 tests/run_mobile_atlas_tests.py
python3 tests/run_mobile_state_tests.py
python3 tests/run_mobile_lifecycle_tests.py
python3 tests/run_mobile_upload_tests.py
python3 tests/run_mobile_geometry_tests.py
python3 tests/run_mobile_ground_tests.py
python3 tests/run_mobile_shader_tests.py
```

The C++ tests compile selected production functions against small fake Cocos/GL
APIs with AddressSanitizer and UndefinedBehaviorSanitizer. In containers that
cannot run LeakSanitizer, use `ASAN_OPTIONS=detect_leaks=0`. The shader test uses
a headless Mesa GLES context through libEGL; it is not a Geometry Dash Android
or phone-driver test.

Coverage includes mixed stock/GPU ordering and fallback, sprite budgets and
index reuse, affine transforms and visibility, level setup/exit lifecycle,
texture upload ranges and retry behavior, live sprite geometry, and compiling /
rendering the GLES shaders on Mesa. Passing these checks does not prove Android
native CI, Geode hook compatibility, level correctness, FPS, or input latency on
a device.
