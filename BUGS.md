# Known limitations (Android port)

- The Android64 Geode/NDK build has not yet been run; host-side source and Mesa
  tests are not native Android CI.
- No Geometry Dash phone test has been performed. Visual correctness, crashes,
  frame-time changes, and input latency are unknown on device.
- This is a conservative GLES2 GPU-assist renderer, not a port of the Windows
  compute-shader pipeline. Feature coverage and performance may differ.
- Device drivers without the required GLES extensions or vertex texture support
  may keep more objects on Geometry Dash's stock renderer.
- Android32 is not built by this first revision.
