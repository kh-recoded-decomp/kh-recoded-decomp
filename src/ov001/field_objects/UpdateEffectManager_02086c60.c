#include "nitro/types.h"

typedef struct EffectNode EffectNode;
typedef void *(*EffectUpdate)(EffectNode *node);

struct EffectNode {
    EffectNode *next;
    u8 pad_04[8];
    EffectUpdate update;
};

typedef struct EffectManager {
    u8 pad_00[5];
    u8 flags;
    u8 pad_06[2];
    EffectNode *nodes;
} EffectManager;

extern EffectManager *data_ov001_020a04dc;
extern void func_ov001_02086b1c(void);
extern BOOL func_ov001_0206e584(void);
extern void func_ov001_02087054(int enable);
extern int func_ov001_02067ed4(void);
extern BOOL IsNodeFlagBitClear_020872b8(EffectNode *node);

void UpdateEffectManager_02086c60(void)
{
    EffectManager *manager = data_ov001_020a04dc;
    EffectNode *node;
    EffectNode *next;
    EffectUpdate update;

    if (manager->flags & 0x80) {
        func_ov001_02086b1c();
        data_ov001_020a04dc->flags &= 0x7f;
    }
    if (data_ov001_020a04dc->flags & 0x51) {
        if (!func_ov001_0206e584() && (data_ov001_020a04dc->flags & 0x40)) {
            func_ov001_02087054(0);
        }
        return;
    }
    if (func_ov001_02067ed4() < 0) {
        return;
    }
    for (node = manager->nodes; node != NULL; node = next) {
        next = node->next;
        if (IsNodeFlagBitClear_020872b8(node) && node->update != NULL) {
            update = node->update(node);
            if (update != NULL) {
                node->update = update;
            }
        }
    }
}
