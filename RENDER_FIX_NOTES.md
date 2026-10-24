# Android GLES2 renderer notes

The Android build does not compile the upstream desktop compute renderer. It
uses a conservative GLES2 GPU-assist path derived from the mobile renderer
architecture: Geometry Dash remains the source of truth for gameplay and
resolved visual state; uncertain objects remain on the native renderer.

The backend avoids desktop-only compute shaders, shader-storage buffers,
indirect multi-draw calls, and WGL entry points. The Android Geode header is
selected through a narrow compatibility shim; ES2 integer-like vertex metadata
is passed as float attributes. CPU shadow buffers are used where GLES2 has no
portable buffer readback API.

The existing host regressions exercise atlas ordering, ownership/fallback,
resolved state, level lifecycle, dirty data uploads, live geometry, and shader
compilation on Mesa GLES. These tests do not replace an Android64 build or a
phone test. No frame-rate or input-latency improvement is claimed.
