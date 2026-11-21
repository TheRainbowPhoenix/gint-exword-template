# gint EX-word EXIT test

Minimal native EX-word `.d01` project derived from the build/packaging setup in
[EXWord-Explorer](https://github.com/TheRainbowPhoenix/EXWord-Explorer).
It uses [gint-exword](https://github.com/TheRainbowPhoenix/gint-exword/tree/exword)
to investigate whether EXIT is missed, the display is stale, or the OS relaunches the app.

## Test on a device

1. Install the `GINTT` package for your device locale (`ja` or `cn`) from
   [GitHub Actions](https://github.com/TheRainbowPhoenix/gint-exword-template/actions).
   The test uses its own app ID, so it does not replace EXWord-Explorer.
2. Start the app and note the hexadecimal `BOOT ID`.
3. Press **EXIT** once. The app displays `EXIT RECEIVED` for about half a
   second, then returns `-2` to the EX-word OS.
4. If the app appears again, compare the `BOOT ID`. A different ID means
   `main()` ran again; the same ID suggests the old framebuffer might still
   be visible. If `EXIT RECEIVED` never appears, investigate input polling.

The ID is sampled from `rtc_ticks()` at entry; do not interpret an identical
value as absolute proof unless enough time has passed between launches.

## Build

The GitHub Actions workflow builds the EX-word fxSDK, the `exword` branch of
gint-exword, and Japanese/Chinese installable folders using the metadata
templates from [exword-xd-a8500-TEST](https://github.com/TheRainbowPhoenix/exword-xd-a8500-TEST).

For a local build with those tools installed, configure CMake with the EX-word
toolchain, installed gint prefix, and `-DEXWORD_METADATA_SOURCE=/path/to/exword-xd-a8500-TEST`,
then build the project. The resulting `ginttest.d01` and install folders
are in the build directory.

Application ID: `GINTT` · D01 filename: `ginttest.d01` · D01 module name: `gintt`.
