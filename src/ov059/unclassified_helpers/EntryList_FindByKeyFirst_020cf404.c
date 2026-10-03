#include "nitro/types.h"

typedef struct {
    union {
        u32 value;
        struct {
            u16 first;
            u16 second;
        } pair;
    } key;
    s32 kind;
} EntryKey;

extern int func_ov059_020cf490(void *list, u16 id);
extern int func_ov059_020cf41c(void *list, u32 value);

int EntryList_FindByKeyFirst_020cf404(void *list, EntryKey *key)
{
    if (key->kind == 2) {
        return func_ov059_020cf490(list, key->key.pair.first);
    }
    return func_ov059_020cf41c(list, key->key.value);
}
