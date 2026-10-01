#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xEC];
    s32 cursorIndex;
    u8 pad_0F0[0x48];
    s32 unk_138;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04b0;

extern BOOL IsModeSetOrFlag370aClear_0207259c(void);
extern BOOL func_ov001_0207531c(void);
extern void *func_ov001_020754d8(FieldMenu *menu, int listKind, int entryId, s32 *outIndex);
extern void func_ov001_020769f4(FieldMenu *menu);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void SelectFieldMenuEntryById_02077f3c(int entryId)
{
    FieldMenu *menu = data_ov001_020a04b0.menu;

    if (menu->unk_138 == 0) {
        return;
    }
    if (!IsModeSetOrFlag370aClear_0207259c()) {
        return;
    }
    if (func_ov001_0207531c()) {
        return;
    }
    func_ov001_020754d8(menu, 0, entryId, &menu->cursorIndex);
    func_ov001_020769f4(menu);
    PlaySoundEffect_0204d924(0, 0);
}
