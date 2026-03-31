#ifndef GODLY_COLOR_LAB_PLUGIN_H
#define GODLY_COLOR_LAB_PLUGIN_H

#include <cstring>
#include <cmath>
#include <algorithm>

#ifdef WINDOWS
#define NOMINMAX
#endif

// OpenFX headers
#include "ofxImageEffect.h"
#include "ofxMemory.h"
#include "ofxPixelFormat.h"

class GodlyColorLabPlugin {
public:
    GodlyColorLabPlugin();
    ~GodlyColorLabPlugin();

    // Initialization
    OfxStatus initialize();
    OfxStatus describe(OfxImageEffectHandle handle);
    OfxStatus describeInContext(OfxImageEffectHandle handle, OfxImageClipPreferenceArgs *args);

    // Processing
    OfxStatus getRegionOfDefinition(OfxImageEffectHandle handle, OfxTime time, OfxRectD *rod);
    OfxStatus render(OfxImageEffectHandle handle, OfxRenderArguments *args);

    // Parameters
    OfxStatus createParameters(OfxImageEffectHandle handle);

    // Utility functions
    void applyColorCorrection(float *pixelData, int width, int height, int pixelComponentCount);
    void applyCurves(float &r, float &g, float &b);
    void applyLevels(float &r, float &g, float &b);
    void applyHSL(float &r, float &g, float &b);
    void applyColorBalance(float &r, float &g, float &b);
    void applyGamma(float &r, float &g, float &b);

private:
    // Parameter handles
    OfxParamHandle curveParam;
    OfxParamHandle levelsParam;
    OfxParamHandle hslParam;
    OfxParamHandle colorBalanceParam;
    OfxParamHandle gammaParam;
    OfxParamHandle enableParam;
};

#endif // GODLY_COLOR_LAB_PLUGIN_H
