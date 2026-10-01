#include "nitro/types.h"

typedef struct {
    u32 flags;
    u32 enabled;
    u32 unk_08;
    u32 unk_0C;
} ObjManagerConfig;

typedef struct {
    void *classObject;
    u32 bufferBase;
    u8 pad_08[0x10];
    u8 objManager[1];
} OverlayWork;

extern void InitObjManager_0204efa8(void *manager, ObjManagerConfig *config);

#define g_overlayWork (*(OverlayWork **)0x020c3844)

void InitOverlayObjManager_020bf478(void) {
    ObjManagerConfig config;
    OverlayWork *work = g_overlayWork;
    config.flags = (((work->bufferBase + 0x8000) & 0xfffffc) << 7) | 0x80000013;
    config.enabled = 1;
    config.unk_08 = 0;
    config.unk_0C = 0;
    InitObjManager_0204efa8(work->objManager, &config);
}
