#include "nitro/types.h"

typedef struct GroupRequest {
    u8 kind;
    u8 pad_01[0x24];
    u8 enabled;
    u8 pad_26[2];
    u16 effectId;
    u16 effectArg;
} GroupRequest;

typedef struct FieldMenu FieldMenu;
struct FieldMenu {
    u8 pad_000[0x1f8];
    void (*onRefresh)(FieldMenu *menu, int a, int b);
    u8 pad_1fc[0x564];
    s32 holdTimer;
    u8 pad_764[4];
    int closeRequested;
    u8 pad_76c[0x240];
    u64 flags;
    u8 selectionIndex;
    u8 pad_9b5[0x681];
    s8 pendingSlot;
    u8 pad_1037[0xb5];
    void (*onClose)(FieldMenu *menu, int arg);
};

extern s16 *GetPlayerFlagRecord_0205036c(int index);
extern void func_ov021_020a8ab4(GroupRequest *request);
extern int func_ov001_0206db8c(int kind);
extern int func_ov021_020a8ca0(GroupRequest *request, int groupId);
extern void SNDi_LockMutex_020bda88(void);
extern void SNDi_LockMutex_020bda98(void);
extern void func_ov040_020bdaa8(void);
extern int func_ov001_02078494(void);
extern void TickFieldMenuEntry_02078000(int list, int slot);
extern int TickSlotTimer_0205031c(int slot);
extern void FieldMenu_TryOpenByMode_02077d64(void);
extern void func_ov001_02078680(void);

void ApplyPendingFlagReward_020bdc94(FieldMenu *menu) {
    if ((menu->flags & 0x4000) == 0 && menu->holdTimer >= 0x9000) {
        s16 *record = GetPlayerFlagRecord_0205036c(menu->pendingSlot);
        GroupRequest request;
        int slot;
        int list;

        if (*record == -1) {
            menu->flags |= 0x4000;
            menu->pendingSlot = -1;
            return;
        }
        func_ov021_020a8ab4(&request);
        request.kind = menu->selectionIndex;
        request.enabled = 1;
        request.effectId = 0x1a0;
        request.effectArg = 0xe;
        func_ov021_020a8ca0(&request, func_ov001_0206db8c(6));
        switch (*record) {
        case 0xd0:
            SNDi_LockMutex_020bda88();
            break;
        case 0xd1:
            SNDi_LockMutex_020bda98();
            break;
        case 0xd2:
            func_ov040_020bdaa8();
            break;
        }
        menu->flags |= 0x4000;
        slot = menu->pendingSlot;
        list = func_ov001_02078494();
        TickFieldMenuEntry_02078000(list, slot);
        if (TickSlotTimer_0205031c(menu->pendingSlot) > 0) {
            FieldMenu_TryOpenByMode_02077d64();
        }
        func_ov001_02078680();
        menu->pendingSlot = -1;
    }
    if (menu->closeRequested != 0) {
        menu->flags &= ~(u64)0x4000;
        menu->onClose(menu, 1);
        if (menu->onRefresh != NULL) {
            menu->onRefresh(menu, 0, -1);
        }
    }
}
