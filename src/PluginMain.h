#include "GodlyColorLabPlugin.h"

// Global plugin instance
GodlyColorLabPlugin *gGodlyColorLabPlugin = nullptr;

// OpenFX required global suite pointers
OfxImageEffectSuiteV1 *gImageEffectSuite = nullptr;
OfxPropertySuiteV1 *gPropertySuite = nullptr;
OfxParameterSuiteV1 *gParameterSuite = nullptr;
OfxMemorySuiteV1 *gMemorySuite = nullptr;
OfxImageEffectHost *gOFXHost = nullptr;

// Plugin entry point
extern "C" {

#ifdef WINDOWS
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

// Called when the plugin is first loaded
EXPORT OfxExport OfxGetNumberOfPlugins(void) {
    return 1;
}

// Called to get plugin info
EXPORT OfxExport OfxPlugin *OfxGetPlugin(int nth) {
    static OfxPlugin plugin = {
        /* pluginApi */          kOfxImageEffectPluginApi,
        /* apiVersion */         kOfxImageEffectPluginApiVersion,
        /* pluginIdentifier */   "com.example.GodlyColorLabPlugin",
        /* pluginVersionMajor */ 1,
        /* pluginVersionMinor */ 0,
        /* hostMinorVersion */   0,
        /* hostMajorVersion */   1,
        /* setHost */            OfxSetHost,
        /* mainEntry */          OfxMainEntry
    };
    return (nth == 0) ? &plugin : nullptr;
}

// Set the host pointer
OfxStatus OfxSetHost(OfxHost *host) {
    gOFXHost = (OfxImageEffectHost *)host;

    gImageEffectSuite = (OfxImageEffectSuiteV1 *)
        host->fetchSuite(host->host, kOfxImageEffectSuite, kOfxImageEffectSuiteVersion);
    gPropertySuite = (OfxPropertySuiteV1 *)
        host->fetchSuite(host->host, kOfxPropertySuite, kOfxPropertySuiteVersion);
    gParameterSuite = (OfxParameterSuiteV1 *)
        host->fetchSuite(host->host, kOfxParameterSuite, kOfxParameterSuiteVersion);
    gMemorySuite = (OfxMemorySuiteV1 *)
        host->fetchSuite(host->host, kOfxMemorySuite, kOfxMemorySuiteVersion);

    if (!gImageEffectSuite || !gPropertySuite || !gParameterSuite) {
        return kOfxStatFailed;
    }

    return kOfxStatOK;
}

// Main plugin entry point for all actions
OfxStatus OfxMainEntry(const char *action, const void *handle, OfxPropertySetHandle inArgs,
                       OfxPropertySetHandle outArgs) {
    try {
        if (std::strcmp(action, kOfxActionLoad) == 0) {
            gGodlyColorLabPlugin = new GodlyColorLabPlugin();
            return gGodlyColorLabPlugin->initialize();
        }
        else if (std::strcmp(action, kOfxActionUnload) == 0) {
            if (gGodlyColorLabPlugin) {
                delete gGodlyColorLabPlugin;
                gGodlyColorLabPlugin = nullptr;
            }
            return kOfxStatOK;
        }
        else if (std::strcmp(action, kOfxImageEffectActionDescribe) == 0) {
            OfxImageEffectHandle effectHandle = (OfxImageEffectHandle)handle;
            return gGodlyColorLabPlugin->describe(effectHandle);
        }
        else if (std::strcmp(action, kOfxImageEffectActionDescribeInContext) == 0) {
            OfxImageEffectHandle effectHandle = (OfxImageEffectHandle)handle;
            OfxImageClipPreferenceArgs *args = (OfxImageClipPreferenceArgs *)inArgs;
            return gGodlyColorLabPlugin->describeInContext(effectHandle, args);
        }
        else if (std::strcmp(action, kOfxImageEffectActionRender) == 0) {
            OfxImageEffectHandle effectHandle = (OfxImageEffectHandle)handle;
            OfxRenderArguments *args = (OfxRenderArguments *)inArgs;
            return gGodlyColorLabPlugin->render(effectHandle, args);
        }

        return kOfxStatReplyDefault;
    }
    catch (...) {
        return kOfxStatFailed;
    }
}

} // extern "C"
