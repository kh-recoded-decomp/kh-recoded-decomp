#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    u32 vramBase;
} ScriptScreen;

extern ScriptScreen data_ov021_020b5620;

u32 MakePaletteUploadParams20_020a95ec(u32 index) {
    return 0x80000000 | (((data_ov021_020b5620.vramBase + 0x8000) & 0xfffffc) << 7) | ((index + 0x14) & 0x1ff);
}
