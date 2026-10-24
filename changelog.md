# v0.1.2-android.1 (source port, not yet a native build)

- Add an unofficial Android64 GLES2 backend for Geometry Dash 2.2081.
- Keep gameplay and uncertain visual ownership in Geometry Dash's stock renderer.
- Add Android64 Geode build workflow and static port checks.
- Rename the mobile renderer, resources, and host regression fixtures.
- Retain upstream attribution and GPL license; remove the optional sprite-sheet
  editor and its bundled Geometry Dash atlas images because they are not needed
  to build the mod.
- Host sanitizer and Mesa GLES tests pass. Android native CI and phone testing
  remain pending.
