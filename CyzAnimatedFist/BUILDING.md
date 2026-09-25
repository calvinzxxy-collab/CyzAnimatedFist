# Building Cyz Animated Fist

## Requirements

- Windows or another environment capable of producing 32-bit Windows binaries
- MinGW-w64 **i686** toolchain
- An ASI Loader is required only for running/testing the resulting plugin

The source intentionally resolves the Windows APIs it needs at runtime and does
not rely on a normal import table.

## Example MinGW-w64 command

From the repository root:

```bat
mkdir build
i686-w64-mingw32-gcc -Os -shared -nostdlib ^
  -Wl,--entry,_DllMain@12 ^
  -Wl,--subsystem,windows ^
  -Wl,--image-base,0x10000000 ^
  -Wl,--dynamicbase ^
  -Wl,--nxcompat ^
  -o build\CyzAnimatedFist.asi src\CyzAnimatedFist.c
```

Depending on your MinGW-w64 distribution, the decorated entry-point spelling may
differ. If the linker cannot find `_DllMain@12`, inspect the generated object with
`nm` and use the symbol name reported for `DllMain`.

## Runtime files

Place the compiled plugin in the GTA San Andreas folder and provide:

```text
modloader/<any folder name>/fist.gif
```

The GIF filename must be `fist.gif`.

## Important

This source uses GTA/RenderWare addresses for the targeted GTA SA 1.0 US layout.
Do not assume those addresses are valid for other executables.
