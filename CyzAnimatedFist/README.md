# Cyz Animated Fist

Open-source animated GIF fist HUD plugin for **GTA San Andreas / SA-MP**.

Cyz Animated Fist replaces the default Fist / Unarmed HUD texture with frames
decoded from a custom `fist.gif` stored somewhere under the `modloader` folder.

## Features

- Animated GIF as the Fist / Unarmed HUD icon
- Recursively searches `modloader` for `fist.gif`
- The Mod Loader subfolder name can be anything
- GIF size limit: **100,000,000 bytes (100 MB)**
- Uses GDI+ to decode GIF frames
- No external builder application required
- Safe fallback: if the expected game layout or GIF is unavailable, the plugin does nothing
- Does not patch GTA code with JMP/CALL hooks

## Installation

1. Install an ASI Loader for GTA San Andreas.
2. Copy `CyzAnimatedFist-SAFE.asi` to your GTA San Andreas directory.
3. Create any folder under `modloader`.
4. Put your animation in that folder and name it exactly:

```text
fist.gif
```

Example:

```text
GTA San Andreas/
├─ CyzAnimatedFist-SAFE.asi
└─ modloader/
   └─ My Animated Fist/
      └─ fist.gif
```

The folder name can be anything. The GIF filename must remain `fist.gif`.

## Compatibility

The SAFE source currently targets the expected memory layout of:

- GTA San Andreas 1.0 US
- Windows x86
- SA-MP setups that run on a compatible GTA SA 1.0 US executable

Different `gta_sa.exe` builds may require different addresses.

## Building

See [BUILDING.md](BUILDING.md).

## Source layout

```text
CyzAnimatedFist/
├─ src/
│  └─ CyzAnimatedFist.c
├─ release/
│  └─ CyzAnimatedFist-SAFE.asi
├─ BUILDING.md
├─ LICENSE
└─ README.md
```

## Contributing

Issues and pull requests are welcome. When changing game addresses or RenderWare
behavior, please document which GTA executable/version was tested.

## License

Released under the [MIT License](LICENSE).

## Author

**CYZ / Cyzennn**
