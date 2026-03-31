# Installing in DaVinci Resolve

## Plugin Location

DaVinci Resolve looks for plugins in specific directories:

### Windows
```
C:\Users\<username>\AppData\Roaming\DaVinci Resolve\Plugins\OpenFX
```

### macOS
```
~/Library/Application Support/DaVinci Resolve/Plugins/OpenFX
```

### Linux
```
~/.local/share/DaVinci Resolve/Plugins/OpenFX
```

## Installation Steps

1. **Build the plugin** (see [BUILDING.md](BUILDING.md))

2. **Create plugin directory** (if it doesn't exist):
   - Navigate to the DaVinci Resolve plugin folder above
   - Create an `OpenFX` subdirectory if needed

3. **Copy the plugin file**:
   - Copy `bin/GodlyColorLab.ofx` to the plugin directory

4. **Restart DaVinci Resolve**

## Verifying Installation

1. Open DaVinci Resolve
2. Go to **Fusion** > **Nodes** or **Color** tab
3. Look for **Color Correction** plugin in the effects list
4. The plugin should appear under **Color** category

## Troubleshooting

### Plugin doesn't appear

- Verify file is named exactly `GodlyColorLab.ofx`
- Check it's in the correct plugin directory for your OS
- Ensure you restarted DaVinci Resolve
- Check DaVinci Resolve log files for loading errors

### Plugin crashes when loading

- Verify plugin was compiled for your OS/architecture
- Check OpenFX SDK version compatibility (1.4+)
- Review console output for error messages

### Plugin loads but has no effect

- Verify parameters are wired to the nodes correctly
- Check that input image has valid pixel data
- Ensure color space is linear (floating-point)
