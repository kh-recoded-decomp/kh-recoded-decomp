#include "nitro/types.h"

typedef struct ActorManager {
    u8 pad_000[0x3EE0];
    void *releasableHandle;
} ActorManager;

extern ActorManager *g_actorManager_020a04e0;
extern void func_0202cd78(void *block);
extern void func_020365f0(void);
extern void func_ov001_0206375c(void);
extern s32 func_ov001_02063a38(void);
extern s32 func_ov001_020645c8(s32 id);
extern void func_ov001_020645e8(s32 id);
extern void func_ov001_0206e444(s32 flag);
extern s32 func_ov001_0207187c(void);
extern void func_ov001_020888dc(void);
extern s32 func_ov001_0208b95c(void);
extern void func_ov001_0208be1c(void);
extern void func_ov040_020bdb84(void);

s32 func_ov001_02088308(void)
{
    ActorManager *manager;
    s32 result;
    s32 sessionMode;

    manager = g_actorManager_020a04e0;
    result = func_ov001_0207187c();
    if (result != 0 && (result = func_ov001_0208b95c(), result != 0)) {
        func_ov001_0208be1c();
        func_020365f0();
        func_ov001_020888dc();
        func_ov001_0206375c();
        func_ov001_0206e444(1);
        func_0202cd78(manager->releasableHandle);
        manager->releasableHandle = 0;
        sessionMode = func_ov001_02063a38();
        if (sessionMode == 6 && (sessionMode = func_ov001_020645c8(0x3628), sessionMode != 0) &&
            (sessionMode = func_ov001_020645c8(0x363c), sessionMode == 0)) {
            func_ov001_020645e8(0x3628);
            func_ov040_020bdb84();
        }
        return 0x20882ad;
    }
    return 0;
}
