#include "nitro/types.h"

typedef struct {
    s32 kind;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} FieldMenuEntry;

extern BOOL IsFieldFlag13OrSessionFlagSet(void);
extern BOOL func_ov001_020645c8(u32 value);
extern BOOL func_ov001_02077118(FieldMenuEntry *entry);

BOOL func_ov001_02077148(void *menu, FieldMenuEntry *entry)
{
    if (IsFieldFlag13OrSessionFlagSet()) {
        if (entry->unk_08 != -1) {
            if (func_ov001_020645c8(0x360a)) {
                return FALSE;
            }
            return func_ov001_02077118(entry);
        }
        if (entry->unk_0C != -1) {
            if (func_ov001_020645c8(0x3609)) {
                return FALSE;
            }
            return func_ov001_02077118(entry);
        }
        return func_ov001_02077118(entry);
    }
    return func_ov001_02077118(entry);
}
