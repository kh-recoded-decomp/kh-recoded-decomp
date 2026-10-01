#include "nitro/types.h"

typedef struct PlayerSlot {
    u8 data[0x30];
} PlayerSlot;

typedef struct PlayerRecords {
    u8 data[0x144];
} PlayerRecords;

extern u8 data_020608c8;
extern PlayerSlot data_020609c0[];
extern PlayerRecords data_02060b50[];
extern void func_01ff8830(void *dst, int value, int size);
extern void ResetSlotEntries_0205020c(void);
extern void LoadLevelTable_0204f5f4(void);
extern void ResetParamWord8_02050528(void);

void InitPlayerData_0204f718(void)
{
    int i;

    data_020608c8 = 1;
    for (i = 0; i < 3; i++) {
        func_01ff8830(&data_020609c0[i], 0, sizeof(PlayerSlot));
        func_01ff8830(&data_02060b50[i], 0, sizeof(PlayerRecords));
    }
    ResetSlotEntries_0205020c();
    LoadLevelTable_0204f5f4();
    ResetParamWord8_02050528();
}
