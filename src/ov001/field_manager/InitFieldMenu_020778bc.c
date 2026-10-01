#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x6C];
    s32 unk_6C;
    u8 pad_070[0xA8];
    s32 unk_118;
    void *record;
    u8 pad_120[0x18];
    s32 unk_138;
    u8 pad_13C[0x8];
    s32 unk_144;
    u8 pad_148[0x4];
    s32 unk_14C;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04b0;

extern FieldMenu *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void *GetSceneTagTracker_020711b0(void);
extern void func_01ff8830(void *dst, int value, u32 size);
extern s8 GetCtxModeByte_02068084(void);
extern BOOL func_ov001_020645c8(u32 flagId);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void func_ov001_0207723c(FieldMenu *menu, u32 arg);
extern void func_ov001_020769f4(FieldMenu *menu);
extern int UpdateFieldMenu_020779f0(void);

void *InitFieldMenu_020778bc(u32 *params)
{
    FieldMenu *menu = NNSi_FndGetCurrentRootHeap_0202a764();
    void *tracker = GetSceneTagTracker_020711b0();

    data_ov001_020a04b0.menu = menu;
    func_01ff8830(menu, 0, sizeof(FieldMenu));
    menu->unk_14C = 1;
    menu->unk_118 = 1;
    menu->unk_6C = -1;
    menu->unk_138 = !(GetCtxModeByte_02068084() == 0 && func_ov001_020645c8(0x3520));
    menu->unk_144 = -1;
    menu->record = FindActiveRecordById_020b8184(tracker, 0x20);
    func_ov001_0207723c(menu, *params);
    func_ov001_020769f4(menu);
    return UpdateFieldMenu_020779f0;
}
