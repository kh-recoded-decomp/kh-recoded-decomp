#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MapPoint {
    fx32 x;
    fx32 y;
} MapPoint;

typedef struct MapMenu {
    u8 pad_00[0x40];
    BOOL markerShown;
    u8 pad_44[0x14];
    u8 renderer[0x6444];
    s32 markerSlot;
    u8 pad_64A0[0x3d0];
    s32 maxLevel;
    u8 pad_6874[0x1740];
    BOOL distanceShown;
} MapMenu;

extern BOOL IsObjectFlagClear_0207f7a4(void *object);
extern s32 GetFieldOffset58_02081ea0(void *object);
extern BOOL IsPlayerEntryFlagSet_02050014(int entry, int flag);
extern VecFx32 *func_ov001_0207f810(void *object);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void StartDistanceSqrt_020b613c(const MapPoint *a, const MapPoint *b);
extern s32 SqrtResultRounded_020b6184(void);
extern void func_ov023_020b6278(MapMenu *menu, void *renderer, s32 distance);
extern void func_0204f378(void *owner, int slot, int value);

BOOL UpdateMapTargetDistance_020b6364(MapMenu *menu, void *object)
{
    void *renderer = menu->renderer;
    MapPoint target;
    MapPoint origin;
    VecFx32 *targetPos;
    VecFx32 *playerPos;

    if (!IsObjectFlagClear_0207f7a4(object) || GetFieldOffset58_02081ea0(object) > menu->maxLevel
        || !IsPlayerEntryFlagSet_02050014(0, 9)) {
        if (menu->distanceShown == FALSE) {
            func_0204f378(renderer, menu->markerSlot, 0);
            menu->markerShown = FALSE;
        }
        return TRUE;
    }

    targetPos = func_ov001_0207f810(object);
    playerPos = func_ov001_0206dc4c(0);
    if (playerPos == NULL) {
        return FALSE;
    }
    target.x = targetPos->x;
    target.y = targetPos->z;
    origin.x = playerPos->x;
    origin.y = playerPos->z;
    StartDistanceSqrt_020b613c(&target, &origin);
    func_ov023_020b6278(menu, renderer, SqrtResultRounded_020b6184());
    menu->distanceShown = TRUE;
    return TRUE;
}
