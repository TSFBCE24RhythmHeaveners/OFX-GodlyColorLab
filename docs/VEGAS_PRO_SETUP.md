# Installing in VEGAS Pro

## Plugin Location

VEGAS Pro looks for OpenFX plugins in:

### Windows (Standard)
```
C:\Program Files\VEGAS\VEGAS Pro <version>\OFX Video Plug-Ins
```

### Windows (32-bit)
```
C:\Program Files (x86)\MAGIX\VEGAS Pro <version>\Script Types\OpenFX
```

## Installation Steps

1. **Build the plugin** (see [BUILDING.md](BUILDING.md))

2. **Locate VEGAS Pro installation**:
   - Typical path: `C:\Program Files\MAGIX\VEGAS Pro 18` (adjust version as needed)

3. **Copy the plugin**:
   - Copy `bin/GodlyColorLab.ofx` to the OpenFX plugin directory
   - Create the directory if it doesn't exist

4. **Restart VEGAS Pro**

## Using the Plugin

1. Open VEGAS Pro
2. Insert a video or image on the timeline
3. Right-click on the event
4. Select **Video FX**
5. Look for **Color Correction** in the available effects
6. Drag it onto your video event

## Verifying Installation

1. Open VEGAS Pro
2. Go to **View** > **Plug-In Chooser** (or similar)
3. Search for "Godly Color Lab"
4. The plugin should appear in the list

## Troubleshooting

### Plugin not found

- Verify VEGAS Pro version (18.0+)
- Check plugin directory path matches your VEGAS Pro installation
- Ensure you're copying to the correct architecture folder (32-bit vs 64-bit)
- Restart VEGAS Pro completely

### Plugin crashes

- Verify plugin architecture matches VEGAS Pro (32-bit vs 64-bit)
- Check log files: `Documents\Vegas Pro\Logs\`
- Try rebuilding the plugin with the latest compiler

### Color doesn't change

- Verify the video has valid pixel data
- Check if effects are enabled on the timeline
- Try adjusting parameters via the effect properties panel

## Supported Formats

- 8-bit (255 scale)
- 16-bit (65535 scale)
- 32-bit floating-point (0-1 scale)
