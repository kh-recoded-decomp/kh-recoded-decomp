#include "nitro/types.h"

#pragma define_section sdkModuleParameters ".text" ".text" ".text" RX

typedef struct SDKBuildInfo {
    const void *autoloadListStart;
    const void *autoloadListEnd;
    const void *autoloadStart;
    const void *staticBssStart;
    const void *staticBssEnd;
    const void *compressedStaticEnd;
    u32 sdkVersion;
    u32 nitroCode;
    u32 nitroCodeByteSwapped;
} SDKBuildInfo;

extern u8 data_0205e100[];
extern u8 data_0205e118[];
extern u8 gMainDisplayState[];

__declspec(sdkModuleParameters) const SDKBuildInfo BuildInfo = {
    data_0205e100,
    data_0205e118,
    gMainDisplayState,
    gMainDisplayState,
    (const void *)0x020613e0,
    NULL,
    0x05047532,
    0xdec00621,
    0x2106c0de
};

