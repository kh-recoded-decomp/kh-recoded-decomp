#include "nitro/types.h"

#pragma define_section sdkModuleParameters ".text" ".text" ".text" RX

/* The loader marker precedes the build information and embedded library tags. */
__declspec(sdkModuleParameters) const u32 SDK_ModuleParamsBlock[8] = {
    0, 0, 0, 0, 0x900, 1, 0xdec08133, 0x3381c0de
};

