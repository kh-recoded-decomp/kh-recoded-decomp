#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u8 profile[0x70];
    u8 slotIndex;
    u8 unk_79_0 : 5;
    u8 pending : 1;
    u8 ready : 1;
    u8 unk_79_7 : 1;
    u8 mode : 2;
    u8 unk_7a_2 : 6;
    u8 pad_7b[5];
    u32 slots[4];
} OpponentState;

extern OpponentState *data_ov015_0207e964;
extern unsigned int func_0202a9d0(u16 range);
extern BOOL IsPlayerCardValid_020736e0(void *card);
extern void InitPanelRecordFromProfile_02072d00(void *profile, int value);
extern void GenerateRandomProfile_02072dd8(void *profile, BOOL fillSlots);
extern void InvokePanelCallback_02073598(void *profile);

void PrepareOpponentProfile_020735bc(void)
{
    if (data_ov015_0207e964->pending != 1 || data_ov015_0207e964->ready != 1) {
        return;
    }
    switch (data_ov015_0207e964->mode) {
    case 0:
        if (IsPlayerCardValid_020736e0(data_ov015_0207e964->profile)) {
            InvokePanelCallback_02073598(data_ov015_0207e964->profile);
            break;
        }
        data_ov015_0207e964->slots[data_ov015_0207e964->slotIndex] = 0;
        break;
    case 1:
        if (func_0202a9d0(100) < 25) {
            InitPanelRecordFromProfile_02072d00(data_ov015_0207e964->profile, 0);
        } else {
            GenerateRandomProfile_02072dd8(data_ov015_0207e964->profile, FALSE);
        }
        InvokePanelCallback_02073598(data_ov015_0207e964->profile);
        break;
    case 2:
        InitPanelRecordFromProfile_02072d00(data_ov015_0207e964->profile, 0);
        InvokePanelCallback_02073598(data_ov015_0207e964->profile);
        break;
    case 3:
        if (func_0202a9d0(100) < 25) {
            InitPanelRecordFromProfile_02072d00(data_ov015_0207e964->profile, 1);
        } else {
            GenerateRandomProfile_02072dd8(data_ov015_0207e964->profile, TRUE);
        }
        InvokePanelCallback_02073598(data_ov015_0207e964->profile);
        break;
    }
    data_ov015_0207e964->pending = 0;
    data_ov015_0207e964->ready = 0;
}
