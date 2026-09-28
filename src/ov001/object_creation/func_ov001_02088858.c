#include "nitro/types.h"

typedef struct ActorManager {
    u8 pad_000[0x30C];
    s32 sessionFlag;
    u8 pad_310[0x454];
    u8 pad_764[0x4];
    u32 field_768;
    u8 pad_76c[0x1F0];
    void *actorSlots[0x200];
    u8 partyMembers[3][0xF2C];
} ActorManager;

extern ActorManager *g_actorManager_020a04e0;
extern void func_ov001_020884e0(void);
extern void func_ov001_0208a8b8(void *actor, s32 flag);
extern void func_ov001_0208be1c(void);

s32 func_ov001_02088858(void)
{
    s32 index;
    void *actor;

    func_ov001_020884e0();
    if (g_actorManager_020a04e0->field_768 == 0) {
        index = 0;
        do {
            actor = g_actorManager_020a04e0->actorSlots[index];
            if (actor != 0) {
                func_ov001_0208a8b8(actor, 1);
            }
            index = index + 1;
        } while (index < 0x200);
        index = 0;
        do {
            func_ov001_0208a8b8(g_actorManager_020a04e0->partyMembers[index], 1);
            index = index + 1;
        } while (index < 3);
        if (g_actorManager_020a04e0->sessionFlag != -1) {
            func_ov001_0208be1c();
        }
        return 1;
    }
    return 0;
}
