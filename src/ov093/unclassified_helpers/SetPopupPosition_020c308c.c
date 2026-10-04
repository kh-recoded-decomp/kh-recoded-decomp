#include "nitro/types.h"
#include "nitro/fx_types.h"

#define INT_TO_FX32(n) ((fx32)((float)(n) > 0 ? 0.5f + 4096.0f * (float)(n) : 4096.0f * (float)(n) - 0.5f))

typedef struct {
    fx32 x;
    fx32 y;
} PointFx32;

typedef struct {
    u8 pad_00[0xc];
    void *objManager;
    u8 pad_10[4];
    PointFx32 position;
} PopupManager;

extern PopupManager *g_popupManager_020c50e4;
extern void func_0204f13c(void *objManager, int slotIndex, PointFx32 *position);

void SetPopupPosition_020c308c(int slotIndex, int x, int y, int offsetX, int offsetY)
{
    PopupManager *manager = g_popupManager_020c50e4;
    void *objManager = manager->objManager;
    PointFx32 *position = &manager->position;

    position->x = INT_TO_FX32(x + offsetX);
    position->y = INT_TO_FX32(y + offsetY);
    func_0204f13c(objManager, slotIndex, position);
}
