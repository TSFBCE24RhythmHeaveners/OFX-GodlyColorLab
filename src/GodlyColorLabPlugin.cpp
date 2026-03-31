#include " GodlyColorLabPlugin.h"
#include <cstring>

 GodlyColorLabPlugin:: GodlyColorLabPlugin()
    : curveParam(nullptr), levelsParam(nullptr), hslParam(nullptr),
      colorBalanceParam(nullptr), gammaParam(nullptr), enableParam(nullptr) {
}

 GodlyColorLabPlugin::~ GodlyColorLabPlugin() {
}

OfxStatus  GodlyColorLabPlugin::initialize() {
    return kOfxStatOK;
}

OfxStatus  GodlyColorLabPlugin::describe(OfxImageEffectHandle handle) {
    OfxPropertySetHandle effectProps;
    gOFXHost->imageEffectSuite->getPropertySet(handle, &effectProps);

    // Set plugin metadata
    gOFXHost->propertySuite->propSetString(effectProps, kOfxPropLabel, 0, "Color Correction");
    gOFXHost->propertySuite->propSetString(effectProps, kOfxImageEffectPluginPropGrouping, 0, "Color");
    gOFXHost->propertySuite->propSetInt(effectProps, kOfxImageEffectPropSupportsMultiResolution, 0, 1);
    gOFXHost->propertySuite->propSetInt(effectProps, kOfxImageEffectPropSupportsTiles, 0, 1);
    gOFXHost->propertySuite->propSetInt(effectProps, kOfxImageEffectPropSupportsMultipleClipDepths, 0, 0);
    gOFXHost->propertySuite->propSetInt(effectProps, kOfxImageEffectPropSupportsMultipleClipPARs, 0, 0);

    return kOfxStatOK;
}

OfxStatus  GodlyColorLabPlugin::describeInContext(OfxImageEffectHandle handle,
                                                   OfxImageClipPreferenceArgs *args) {
    OfxPropertySetHandle effectProps;
    gOFXHost->imageEffectSuite->getPropertySet(handle, &effectProps);

    // Describe input clip
    OfxPropertySetHandle inputProps;
    gOFXHost->imageEffectSuite->clipGetPropertySet(handle, kOfxImageEffectSimpleSourceClipName, &inputProps);
    gOFXHost->propertySuite->propSetString(inputProps, kOfxPropLabel, 0, "Source");

    // Describe output clip
    OfxPropertySetHandle outputProps;
    gOFXHost->imageEffectSuite->clipGetPropertySet(handle, kOfxImageEffectOutputClipName, &outputProps);
    gOFXHost->propertySuite->propSetString(outputProps, kOfxPropLabel, 0, "Output");

    return createParameters(handle);
}

OfxStatus  GodlyColorLabPlugin::createParameters(OfxImageEffectHandle handle) {
    OfxParamSetHandle paramSet;
    gOFXHost->imageEffectSuite->getParamSet(handle, &paramSet);

    // Enable/Disable parameter
    OfxPropertySetHandle enableProps;
    gOFXHost->parameterSuite->paramDefine(paramSet, kOfxParamTypeBoolean, "Enable", &enableProps);
    gOFXHost->propertySuite->propSetString(enableProps, kOfxPropLabel, 0, "Enable Color Correction");
    gOFXHost->propertySuite->propSetInt(enableProps, kOfxParamPropDefault, 0, 1);

    // Curves parameters (RGB)
    OfxPropertySetHandle curveProps;
    gOFXHost->parameterSuite->paramDefine(paramSet, kOfxParamTypeDouble, "RedCurve", &curveProps);
    gOFXHost->propertySuite->propSetString(curveProps, kOfxPropLabel, 0, "Red Curve");
    gOFXHost->propertySuite->propSetDouble(curveProps, kOfxParamPropDefault, 0, 0.5);
    gOFXHost->propertySuite->propSetDouble(curveProps, kOfxParamPropMin, 0, 0.0);
    gOFXHost->propertySuite->propSetDouble(curveProps, kOfxParamPropMax, 0, 1.0);

    // Levels parameters
    OfxPropertySetHandle levelsProps;
    gOFXHost->parameterSuite->paramDefine(paramSet, kOfxParamTypeDouble, "BlackLevel", &levelsProps);
    gOFXHost->propertySuite->propSetString(levelsProps, kOfxPropLabel, 0, "Black Level");
    gOFXHost->propertySuite->propSetDouble(levelsProps, kOfxParamPropDefault, 0, 0.0);
    gOFXHost->propertySuite->propSetDouble(levelsProps, kOfxParamPropMin, 0, 0.0);
    gOFXHost->propertySuite->propSetDouble(levelsProps, kOfxParamPropMax, 0, 1.0);

    // Hue/Saturation parameters
    OfxPropertySetHandle hueProps;
    gOFXHost->parameterSuite->paramDefine(paramSet, kOfxParamTypeDouble, "Saturation", &hueProps);
    gOFXHost->propertySuite->propSetString(hueProps, kOfxPropLabel, 0, "Saturation");
    gOFXHost->propertySuite->propSetDouble(hueProps, kOfxParamPropDefault, 0, 1.0);
    gOFXHost->propertySuite->propSetDouble(hueProps, kOfxParamPropMin, 0, 0.0);
    gOFXHost->propertySuite->propSetDouble(hueProps, kOfxParamPropMax, 0, 2.0);

    // Gamma parameter
    OfxPropertySetHandle gammaProps;
    gOFXHost->parameterSuite->paramDefine(paramSet, kOfxParamTypeDouble, "Gamma", &gammaProps);
    gOFXHost->propertySuite->propSetString(gammaProps, kOfxPropLabel, 0, "Gamma");
    gOFXHost->propertySuite->propSetDouble(gammaProps, kOfxParamPropDefault, 0, 1.0);
    gOFXHost->propertySuite->propSetDouble(gammaProps, kOfxParamPropMin, 0, 0.1);
    gOFXHost->propertySuite->propSetDouble(gammaProps, kOfxParamPropMax, 0, 3.0);

    return kOfxStatOK;
}

OfxStatus  GodlyColorLabPlugin::getRegionOfDefinition(OfxImageEffectHandle handle, OfxTime time,
                                                       OfxRectD *rod) {
    OfxImageClipHandle sourceClip;
    gOFXHost->imageEffectSuite->clipGetHandle(handle, kOfxImageEffectSimpleSourceClipName, &sourceClip);

    OfxPropertySetHandle sourceProps;
    gOFXHost->imageEffectSuite->clipGetPropertySet(sourceClip, &sourceProps);

    gOFXHost->propertySuite->propGetDoubleN(sourceProps, kOfxImagePropBounds, 4, (double *)rod);

    return kOfxStatOK;
}

OfxStatus  GodlyColorLabPlugin::render(OfxImageEffectHandle handle, OfxRenderArguments *args) {
    OfxPropertySetHandle outProps;
    gOFXHost->imageEffectSuite->getPropertySet(handle, &outProps);

    // Get clips
    OfxImageClipHandle sourceClip;
    gOFXHost->imageEffectSuite->clipGetHandle(handle, kOfxImageEffectSimpleSourceClipName, &sourceClip);

    OfxImageMemoryHandle sourceImage;
    OfxPropertySetHandle sourceProps;
    gOFXHost->imageEffectSuite->clipGetImage(sourceClip, args->time, nullptr, &sourceImage);
    gOFXHost->imageEffectSuite->imageMemoryGetPropertySet(sourceImage, &sourceProps);

    // Get output image
    OfxImageMemoryHandle outputImage;
    gOFXHost->imageEffectSuite->imageMemoryAlloc(handle, nullptr, &outputImage);
    OfxPropertySetHandle outputProps;
    gOFXHost->imageEffectSuite->imageMemoryGetPropertySet(outputImage, &outputProps);

    // Process pixels
    int width = 0, height = 0;
    gOFXHost->propertySuite->propGetInt(sourceProps, kOfxImagePropRowBytes, 0, &width);
    gOFXHost->propertySuite->propGetInt(sourceProps, kOfxImagePropBounds, 3, &height);

    float *pixelData;
    gOFXHost->propertySuite->propGetPointer(sourceProps, kOfxImagePropData, 0, (void **)&pixelData);

    if (pixelData) {
        applyColorCorrection(pixelData, width, height, 4); // RGBA
    }

    // Release images
    gOFXHost->imageEffectSuite->clipReleaseImage(sourceImage);
    gOFXHost->imageEffectSuite->imageMemoryFree(outputImage);

    return kOfxStatOK;
}

void  GodlyColorLabPlugin::applyColorCorrection(float *pixelData, int width, int height,
                                                  int pixelComponentCount) {
    int pixelCount = width * height;

    for (int i = 0; i < pixelCount; ++i) {
        int pixelIndex = i * pixelComponentCount;

        float r = pixelData[pixelIndex + 0];
        float g = pixelData[pixelIndex + 1];
        float b = pixelData[pixelIndex + 2];
        float a = (pixelComponentCount > 3) ? pixelData[pixelIndex + 3] : 1.0f;

        // Apply color correction operations
        applyCurves(r, g, b);
        applyLevels(r, g, b);
        applyHSL(r, g, b);
        applyColorBalance(r, g, b);
        applyGamma(r, g, b);

        // Clamp values
        r = std::max(0.0f, std::min(1.0f, r));
        g = std::max(0.0f, std::min(1.0f, g));
        b = std::max(0.0f, std::min(1.0f, b));

        // Write back
        pixelData[pixelIndex + 0] = r;
        pixelData[pixelIndex + 1] = g;
        pixelData[pixelIndex + 2] = b;
        if (pixelComponentCount > 3) {
            pixelData[pixelIndex + 3] = a;
        }
    }
}

void  GodlyColorLabPlugin::applyCurves(float &r, float &g, float &b) {
    // Placeholder: Apply curve adjustment
    // In a full implementation, this would use the curve parameter data
    r = r;
    g = g;
    b = b;
}

void  GodlyColorLabPlugin::applyLevels(float &r, float &g, float &b) {
    // Placeholder: Apply levels adjustment
    // In a full implementation, this would adjust black/white/mid-tones
}

void  GodlyColorLabPlugin::applyHSL(float &r, float &g, float &b) {
    // Convert RGB to HSL, adjust saturation, convert back
    // Placeholder implementation
}

void  GodlyColorLabPlugin::applyColorBalance(float &r, float &g, float &b) {
    // Placeholder: Apply color balance adjustments
}

void  GodlyColorLabPlugin::applyGamma(float &r, float &g, float &b) {
    // Apply gamma correction
    // gamma = 1.0 / gamma_value (inverse)
    float gamma = 1.0f / 2.2f; // Standard sRGB gamma
    r = std::pow(r, gamma);
    g = std::pow(g, gamma);
    b = std::pow(b, gamma);
}
