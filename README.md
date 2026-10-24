# Bismuth Android (experimental)

An unofficial Android64 / Geometry Dash 2.2081 Geode port experiment for
[IliasHDZ's Bismuth](https://github.com/iliasHDZ/Bismuth).

## What this port changes

The upstream desktop renderer depends on desktop OpenGL compute shaders and
storage buffers, which are not part of Geometry Dash's Android GLES2 rendering
path. This project therefore uses a separate GLES2 GPU-assist backend. Geometry
Dash remains authoritative for gameplay, triggers, animation, colors, visibility,
and sprite hierarchy. The port only takes ownership of conservative, explicitly
classified render work; uncertain or unsupported visuals remain on Geometry
Dash's stock renderer.

This is **not** a drop-in Android build of the Windows compute renderer. Visual
coverage, speed, and features may differ. It is experimental, has not yet passed
Android native CI or a phone test, and must not be treated as a verified
performance improvement. Android32 is not included in this first target.

The mobile backend is based on the GLES2 renderer work in the
[candyzp/Bismuth fork](https://github.com/candyzp/Bismuth), commit
`d31115ee3851655c6671233bc13b1a42e0d7e157`. See `PORTING-NOTICE.md` and
`LICENSE.md` for provenance and licensing. This port is not affiliated with or
endorsed by IliasHDZ or Geode.

## Build target

- Geometry Dash: Android, `2.2081`
- Architecture: Android64 (`arm64-v8a`)
- Geode SDK minimum declared by the mod: `5.10.1`
- Renderer: OpenGL ES 2.0-compatible path with runtime stock-renderer fallback

Push this source to a GitHub repository and run **Build Bismuth Android64** in
Actions. A successful run should publish an artifact containing a `.geode`
package. CI success proves compilation/package creation only; it does not prove
correct rendering or speed on a phone.

## Safe test flow

1. Keep the normal Geometry Dash renderer available; do not combine this alpha
   with other rendering mods for the first test.
2. Install only after the Android64 Actions job succeeds. If the game crashes,
   use the Geode launcher's safe-mode/disable-mods option and remove this port.
3. Test in a disposable, ordinary level first. Check level entry, reset/restart,
   background changes, fades, moving objects, glow, and exiting the level.
4. For a performance comparison, use the same section, FPS cap, settings, and
   similar device temperature; compare frame-time stability over repeated runs.
5. Share the whole relevant log/status line if anything is missing or misplaced.

The included host-side regression tests exercise selected GLES shader, batching,
state, lifecycle, and upload cases. They are not Android device tests.

## License

This derivative includes the upstream `LICENSE.md` unchanged. The upstream
license is GPL-3.0-or-later with its additional project-specific restriction
about using the project to facilitate Geometry Dash level generation or
modification with generative AI. This rendering port does not generate or modify
levels.
