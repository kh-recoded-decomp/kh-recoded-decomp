#include "nitro/types.h"

typedef void (*ActorCallback)(int actor, int arg1, int arg2);

extern void func_ov001_0206cdec(u32 *record, int extended);
extern void func_ov001_020734f8();
extern int func_ov001_02072040(void);
extern void func_ov001_02071fec(void);
extern int func_ov001_0206db5c(int index);
extern void func_ov001_0206e6c0(u8 value);
extern void func_02038b2c();
extern void func_02035c28(u8 value);
extern void func_ov021_020a8b9c(int index);

extern u32 g_manager_020a049c;

#ifndef ACTOR_SLOT_FLAGS_QUALIFIER
#define ACTOR_SLOT_FLAGS_QUALIFIER
#endif

void func_ov001_0206de40(int index)
{
    int slot;
    int cur;

    cur = g_manager_020a049c;
    if (g_manager_020a049c != 0) {
        if (index == 0) {
            func_ov001_0206cdec((u32 *)(g_manager_020a049c + 0xdc), 1);
            if (*(int *)(cur + 0x90) != 0) {
                func_ov001_020734f8();
                *(u32 *)(cur + 0x90) = 0;
            }
            slot = func_ov001_02072040();
            if (slot != 0) {
                func_ov001_02071fec();
            }
        }
        slot = func_ov001_0206db5c(index);
        if (slot != 0) {
            cur = cur + 4 + index * 0x28;
            *(ACTOR_SLOT_FLAGS_QUALIFIER unsigned short *)(cur + 0x24) =
                *(ACTOR_SLOT_FLAGS_QUALIFIER unsigned short *)(cur + 0x24) & 0xfffd;
            *(ACTOR_SLOT_FLAGS_QUALIFIER unsigned short *)(cur + 0x24) =
                *(ACTOR_SLOT_FLAGS_QUALIFIER unsigned short *)(cur + 0x24) & 0xfff7;
            cur = func_ov001_0206db5c(index);
            if (*(ActorCallback *)(cur + 0x20c) != (ActorCallback)0) {
                (*(ActorCallback *)(cur + 0x20c))(cur, 2, 0);
            }
            func_ov001_0206e6c0(*(u8 *)(slot + 0x1d8));
            func_02038b2c();
            func_02035c28(*(u8 *)(slot + 0x1d8));
        }
        func_ov021_020a8b9c(index);
    }
}
