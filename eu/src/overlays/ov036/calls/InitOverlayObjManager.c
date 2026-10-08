#include "nitro/types.h"

typedef struct ObjManagerConfig {
    u32 flags;
    u32 enabled;
    u32 unk_08;
    u32 unk_0C;
} ObjManagerConfig;

typedef struct OverlayWork {
    void *classObject;
    u32 bufferBase;
    u8 pad_08[0x10];
    u8 objManager[1];
} OverlayWork;

extern OverlayWork *gTextWindowResourceTable[];
extern void InitObjManager(void *manager, ObjManagerConfig *config);

void InitOverlayObjManager(void)
{
    ObjManagerConfig config;
    OverlayWork *work = gTextWindowResourceTable[0];

    config.flags = (((work->bufferBase + 0x8000) & 0xfffffc) << 7) | 0x80000013;
    config.enabled = 1;
    config.unk_08 = 0;
    config.unk_0C = 0;
    InitObjManager(work->objManager, &config);
}
