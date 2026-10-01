#include "nitro/types.h"

typedef struct ActorLink {
    u8 pad_00[0x10];
    u16 active;
} ActorLink;

typedef struct StageManager {
    u32 flags;
    u8 pad_004[0x18d7c - 4];
    void *linkList;
} StageManager;

extern StageManager *data_ov001_020a0508;
extern int Session_Exists_02063a24(void);
extern s32 func_ov001_02063a38(void);
extern BOOL func_ov001_020645c8(u32 value);
extern ActorLink *BindDescriptor0_0208f268(void *list, void *node);
extern void *func_ov001_0208f27c(void *list);
extern void *func_ov001_0208f28c(void *node);
extern void ResetLinkedActorMotion_02097a64(ActorLink *link);

static inline s32 GetSessionMode(void)
{
    if (Session_Exists_02063a24()) {
        return func_ov001_02063a38();
    }
    return 0;
}

void ResetStageLinksForSession_0209c430(void)
{
    BOOL reset;
    void *node;
    ActorLink *link;

    if (data_ov001_020a0508 == NULL) {
        return;
    }
    reset = FALSE;
    if (Session_Exists_02063a24() && func_ov001_020645c8(0x3628)) {
        reset = TRUE;
    } else if (GetSessionMode() == 10 && !func_ov001_020645c8(0x380c)) {
        reset = TRUE;
    } else if (GetSessionMode() == 6 && !func_ov001_020645c8(0x379e)) {
        reset = TRUE;
    }
    if (reset) {
        data_ov001_020a0508->flags |= 0x40;
        node = func_ov001_0208f27c(data_ov001_020a0508->linkList);
        if (node == NULL) {
            return;
        }
        do {
            link = BindDescriptor0_0208f268(data_ov001_020a0508->linkList, node);
            node = func_ov001_0208f28c(node);
            if (link->active != 0) {
                ResetLinkedActorMotion_02097a64(link);
            }
        } while (node != NULL);
        return;
    }
    data_ov001_020a0508->flags |= 2;
}
