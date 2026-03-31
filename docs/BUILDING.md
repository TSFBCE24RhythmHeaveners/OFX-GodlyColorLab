# Building the OpenFX Color Correction Plugin

## Prerequisites

1. **OpenFX SDK** - Download from https://github.com/ofxa/openfx
2. **CMake** 3.15 or later
3. **C++ Compiler**:
   - **Windows**: MSVC 2019 or later (Visual Studio)
   - **macOS**: Clang 10+ (Xcode)
   - **Linux**: GCC 9+ or Clang 10+

## Setup

### 1. Download OpenFX SDK

```bash
# Clone the OpenFX repository
git clone https://github.com/ofxa/openfx.git
cd openfx
# Extract or note the include path
```

### 2. Set Environment Variables

**Windows (Command Prompt)**:
```cmd
set OFX_PATH=C:\path\to\openfx
```

**macOS/Linux (Bash)**:
```bash
export OFX_PATH=/path/to/openfx
```

## Building on Windows

```bash
# Create build directory
mkdir build
cd build

# Configure with Visual Studio 2022
cmake .. -G "Visual Studio 17 2022" -A x64

# Build in Release mode
cmake --build . --config Release

# Output: bin/ColorCorrection.ofx
```

## Building on macOS

```bash
# Create build directory
mkdir build
cd build

# Configure with Unix Makefiles
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build .

# Output: bin/ColorCorrection.ofx
```

## Building on Linux

```bash
# Create build directory
mkdir build
cd build

# Configure
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build .

# Output: bin/ColorCorrection.ofx.so
```

## Troubleshooting

### CMake can't find OpenFX headers

```
Error: OpenFX headers not found at /path/to/openfx/include
```

**Solution**: Verify `OFX_PATH` points to the OpenFX directory (not the include subdirectory).

### Compiler errors about missing ofxImageEffect.h

**Solution**: Ensure the OpenFX SDK is properly extracted and `OFX_PATH` is set correctly.

### Plugin won't load in DaVinci Resolve

- Verify the plugin file extension (.ofx on all platforms)
- Check plugin was built for the correct architecture (x64)
- Consult [DAVINCI_RESOLVE_SETUP.md](DAVINCI_RESOLVE_SETUP.md)

## Cleaning Build

```bash
cd build
cmake --build . --target clean
# Or delete the entire build directory
```
