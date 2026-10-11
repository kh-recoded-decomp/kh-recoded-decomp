#pragma opt_rotateloops off
#pragma opt_propagation off
#include "nitro/types.h"

typedef struct Actor Actor;

typedef struct MenuWork {
    u8 pad_0000[0x1258];
    u32 resultSlot;
    u8 pad_125c[0x1264 - 0x125c];
    int soloSelection;
    int pairSelection;
    u8 pad_126c[0x1274 - 0x126c];
    int rewardKind;
} MenuWork;

struct Actor {
    u8 pad_000[0x9b4];
    u8 selection;
    u8 pad_9b5[0xb2c - 0x9b5];
    u8 menuSound[0x1034 - 0xb2c];
    s8 rewardOrder;
    u8 pad_1035[0x10ec - 0x1035];
    void (*setMode)(Actor *actor, int mode);
};

extern MenuWork *data_ov054_020d3700;
extern void *func_ov001_0206db78(u32 selection);
extern BOOL HasFlagsAt0xc_020a751c(void *holder, u16 mask);
extern int GetSelectedMenuEntryValue_02077f80(void);
extern int ResolveEventVariant_02078948(void);
extern void FieldMenu_TryOpenByMode_02077d64(void);
extern u32 GetBoundedEntryField_0206db5c(int index);
extern BOOL TryRequestEnemyAction_020d64dc(u32 field, int kind, int entry);
extern u32 func_ov021_020a81b8(void *work, u32 value, u32 *resultSlot);
extern int func_ov001_02078494(void);
extern void TickFieldMenuEntry_02078000(int listKind, int entryId);

BOOL HandleFieldMenuSelection_020d34b0(Actor *actor)
{
    MenuWork *work = data_ov054_020d3700;
    BOOL handled;
    BOOL tick;
    int entry;
    int variant;
    void *self = func_ov001_0206db78(actor->selection);

    handled = FALSE;
    if (HasFlagsAt0xc_020a751c(self, 0x400)) {
        entry = GetSelectedMenuEntryValue_02077f80();
        if (entry >= 0) {
            tick = FALSE;
            variant = ResolveEventVariant_02078948();
            switch (variant) {
            case 0xb7:
            case 0xb8:
            case 0xb9:
            case 0xba:
            case 0xbb:
            case 0xbc:
            case 0xbd:
                if (actor != NULL) {
                    actor->rewardOrder = entry;
                    work->rewardKind = variant;
                    actor->setMode(actor, 0x20);
                    handled = TRUE;
                }
                break;
            case 0xf1:
            case 0xf3:
                if (work->soloSelection > 0 && TryRequestEnemyAction_020d64dc(GetBoundedEntryField_0206db5c(work->soloSelection), 2, entry)) {
                    func_ov021_020a81b8(actor->menuSound, 3, &work->resultSlot);
                }
                break;
            case 0xf5:
            case 0xf7:
                if (work->pairSelection > 0 && TryRequestEnemyAction_020d64dc(GetBoundedEntryField_0206db5c(work->pairSelection), 2, entry)) {
                    func_ov021_020a81b8(actor->menuSound, 4, &work->resultSlot);
                }
                break;
            }
            if (tick) {
                TickFieldMenuEntry_02078000(func_ov001_02078494(), entry);
                FieldMenu_TryOpenByMode_02077d64();
            }
        } else {
            FieldMenu_TryOpenByMode_02077d64();
        }
    }
    return handled;
}
