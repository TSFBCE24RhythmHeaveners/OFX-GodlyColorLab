# Godly Color Lab OpenFX Plugin

A professional color correction plugin built with OpenFX that supports **DaVinci Resolve** and **VEGAS Pro**.

## Features

- **Curves Adjustment** - Full RGB and individual channel curves
- **Levels Control** - Black/white/mid-tone adjustments
- **Hue/Saturation** - HSL color adjustments
- **Color Balance** - Shadows, midtones, highlights
- **Gamma Correction** - Linear gamma adjustments
- **Real-time Preview** - Instant visual feedback

## System Requirements

- **DaVinci Resolve** 17.0 or later
- **VEGAS Pro** 18.0 or later
- **CMake** 3.15 or later
- **C++ Compiler** (GCC 9+, Clang 10+, or MSVC 2019+)
- **OpenFX SDK** 1.4 or later

## Quick Start

```bash
# Clone the repository
git clone https://github.com/TSFBCE24RhythmHeaveners/OFX-GodlyColorLab.git
cd openfx-godlycolorlab

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
cmake --build . --config Release

# Plugin output
# DaVinci Resolve: ./bin/GodlyColorLab.ofx
# VEGAS Pro: ./bin/GodlyColorLab.ofx
