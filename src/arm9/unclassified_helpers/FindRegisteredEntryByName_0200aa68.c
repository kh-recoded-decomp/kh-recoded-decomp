#include "nitro/types.h"

typedef struct Registration {
    void *tag;
    struct Registration *next;
    u8 pad_08[0xc];
    u32 flags;
} Registration;

extern void *func_02004938(void);
extern void func_0200494c(void *token);
extern void *ResolveTaggedPointer_0200b034(int *value);
extern int func_02010ce0(int offset, void *context, char *name);
extern Registration *data_020578ec;

Registration *FindRegisteredEntryByName_0200aa68(void *context, char *name) {
    void *token;
    Registration *node;
    int offset;
    int result;
    int flagClear = 0;
    int flagSet = 1;

    token = func_02004938();
    node = data_020578ec;
    while (node != 0) {
        int matches = (node->flags & 2) ? flagSet : flagClear;
        if (matches != 0) {
            offset = (int)ResolveTaggedPointer_0200b034((int *)node);
            result = func_02010ce0(offset, context, name);
            if (result == 0 && name[offset] == 0) {
                break;
            }
        }
        node = node->next;
    }
    func_0200494c(token);
    return node;
}
