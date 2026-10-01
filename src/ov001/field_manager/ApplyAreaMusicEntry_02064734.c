#include "nitro/types.h"

typedef struct AreaMusicEntry {
    int flagValue;
    int overlayId;
} AreaMusicEntry;

typedef struct AreaMusicTable {
    AreaMusicEntry entries[5];
} AreaMusicTable;

typedef struct FieldState {
    u8 pad_00[0x14];
    int overlayId;
    u8 pad_18;
    u8 areaIndex;
} FieldState;

extern const AreaMusicTable data_ov001_0209d878;
extern FieldState *data_ov001_020a0460;
extern void StoreGlobalArrayEntry_02025668(int index, int value);
extern void func_02029f78(int processor, int overlayId);

void ApplyAreaMusicEntry_02064734(int index)
{
    AreaMusicTable table = data_ov001_0209d878;

    if (table.entries[index].flagValue != 0) {
        StoreGlobalArrayEntry_02025668(8, table.entries[index].flagValue);
    }
    if (table.entries[index].overlayId != -1) {
        data_ov001_020a0460->overlayId = table.entries[index].overlayId;
        func_02029f78(0, data_ov001_020a0460->overlayId);
        data_ov001_020a0460->areaIndex = index;
    }
}
