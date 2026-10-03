#include "nitro/types.h"

typedef struct ScreenAsset {
    u8 pad_00[8];
    u32 size;
    u8 data[1];
} ScreenAsset;

typedef struct AssetSlot {
    ScreenAsset *asset;
    u8 pad_04[8];
} AssetSlot;

typedef struct MovieScene {
    u8 pad_000[0x8d8];
    AssetSlot slots[1];
} MovieScene;

typedef struct BgRequest {
    u8 pad_00[6];
    u16 slot;
    u16 plane;
} BgRequest;

extern void GX_LoadBG0Scr_02007550(const void *src, u32 offset, u32 size);
extern void GX_LoadBG1Scr_02007630(const void *src, u32 offset, u32 size);
extern void GX_LoadBG2Scr_02007710(const void *src, u32 offset, u32 size);

BOOL MovieScene_LoadBgScreen_0206409c(MovieScene *scene, void *unused, BgRequest *request)
{
    ScreenAsset *asset = scene->slots[request->slot].asset;

    switch (request->plane) {
    case 1:
        GX_LoadBG0Scr_02007550(asset->data, 0, asset->size);
        break;
    case 2:
        GX_LoadBG1Scr_02007630(asset->data, 0, asset->size);
        break;
    case 4:
        GX_LoadBG2Scr_02007710(asset->data, 0, asset->size);
        break;
    }
    return TRUE;
}
