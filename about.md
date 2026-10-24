# Bismuth Android port

This is an unofficial experimental Android64 GLES2 rendering port of
[IliasHDZ's Bismuth](https://github.com/iliasHDZ/Bismuth) for Geometry Dash
2.2081 and the Geode mod loader.

The Android renderer is deliberately different from the upstream Windows compute
renderer. Geometry Dash remains responsible for gameplay, triggers, animation,
colors, visibility, and sprite hierarchy. Bismuth only GPU-assists conservative
render work after checking ownership and state; uncertain visuals stay on the
stock renderer.

This build is not yet validated by Android native CI or by a phone. It may omit
features, render some levels incorrectly, or be slower than Geometry Dash. Do
not use it for serious play or assume a performance gain until the exact device
and level segment have been tested.

See `README.md`, `PORTING-NOTICE.md`, and `LICENSE.md` before building or
redistributing.
