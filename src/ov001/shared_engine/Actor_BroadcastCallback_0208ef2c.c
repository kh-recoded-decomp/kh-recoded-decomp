#include "nitro/types.h"

typedef struct ActorWithCallback {
    u8 pad_000[0x10ec];
    void (*callback)(void *self, int arg);
} ActorWithCallback;

extern int func_ov001_0206dc38(void);
extern ActorWithCallback *func_ov001_0206db5c(int index);
extern void func_ov058_020d6c78(void);

u32 Actor_BroadcastCallback_0208ef2c(void)
{
    int index;
    int count;
    ActorWithCallback *actor;

    index = 1;
    count = func_ov001_0206dc38();
    if (1 < count) {
        do {
            actor = func_ov001_0206db5c(index);
            func_ov058_020d6c78();
            actor->callback(actor, 1);
            index = index + 1;
            count = func_ov001_0206dc38();
        } while (index < count);
    }
    return 1;
}
