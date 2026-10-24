# Port checklist

- [x] Declare Geometry Dash Android 2.2081 and Android64 Geode target.
- [x] Route shared GL headers to GLES2 and add mobile attribute wrappers.
- [x] Preserve the stock renderer for unsupported/uncertain visuals.
- [x] Add Android64 CI workflow and a port-configuration check.
- [x] Run the host-side renderer, lifecycle, upload, and Mesa GLES tests.
- [ ] Pass a fresh Android64 Geode/NDK native build.
- [ ] Inspect the generated `.geode` package and manifest.
- [ ] Test install, level entry, restart, effects, and exit on a disposable phone level.
- [ ] Measure frame time before claiming any speed improvement.
- [ ] Consider Android32 only after Android64 build and device validation.
