#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x60c];
    int slotValues[2];
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04a4;

extern void LoadSlotIconGraphics_0207001c(int slot, int iconId);
extern int func_ov001_0207162c(int a, int b, int c, int d);
extern BOOL IsFieldFlag8Set_020728a4(void);
extern BOOL func_ov001_020728e4(void);
extern void func_ov001_02078710(s32 index, s32 kind);

void SetFieldSlotValue_020715d4(int index, int value, int param, int extra)
{
    if (value == -1 || index < 0 || index > 1) {
        return;
    }
    data_ov001_020a04a4.manager->slotValues[index] = value;
    LoadSlotIconGraphics_0207001c(index, value);
    func_ov001_0207162c(index + 1, extra, param, extra);
    if (IsFieldFlag8Set_020728a4() || func_ov001_020728e4()) {
        func_ov001_02078710(index, value);
    }
}
