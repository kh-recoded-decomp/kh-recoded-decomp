#include "nitro/types.h"

typedef struct AreaDef {
    u8 unk_00;
    u8 level : 7;
    u8 alertActive : 1;
    s16 progress;
    u8 clearedCount;
    u8 objectCount;
    u8 pendingEventCount;
    u8 eventCount;
    u8 pad_08[0x14];
} AreaDef;

typedef struct FieldState {
    u8 pad_00[0x50];
    AreaDef *areas;
} FieldState;

extern FieldState *data_ov035_020bc4e0;
extern void func_ov040_020bc754(int areaIndex, int level);
extern u32 SubScene9_Request_02066e50(u8 value);
extern void func_0204d8d0(int soundId, int volume);

void UpdateAreaProgressLevel_020bc784(int areaIndex)
{
    AreaDef *area;
    int level;
    int progress;
    int oldLevel;

    if (areaIndex < 0) {
        return;
    }
    area = &data_ov035_020bc4e0->areas[areaIndex];
    progress = area->clearedCount * 2 + area->pendingEventCount * 10;
    if (progress > 100) {
        progress = 100;
    }
    if (progress >= 100) {
        level = 3;
    } else if (progress >= 40) {
        level = 2;
    } else {
        level = 1;
        if (progress < 1) {
            level = 0;
        }
    }
    if (area->level != level) {
        func_ov040_020bc754(areaIndex, level);
        oldLevel = area->level;
        if ((u32)oldLevel <= 3) {
            if (level == 0 && area->alertActive) {
                area->alertActive = 0;
                SubScene9_Request_02066e50(0);
            } else if (level < oldLevel) {
                func_0204d8d0(0x1a0, 0x2b);
            }
        }
    }
    area->level = level;
    area->progress = progress;
}
