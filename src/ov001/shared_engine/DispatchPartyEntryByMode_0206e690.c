#include "nitro/types.h"

typedef struct PartyState {
    int mode;
} PartyState;

extern PartyState *data_ov001_020a049c;
extern u32 GetBoundedEntryField_0206db5c(int index);
extern int func_ov052_020cfb28(u32 entry);
extern int func_ov059_020cd124(u32 entry);

int DispatchPartyEntryByMode_0206e690(int index)
{
    switch (data_ov001_020a049c->mode) {
    case 0:
    case 2:
        return func_ov052_020cfb28(GetBoundedEntryField_0206db5c(index));
    case 1:
        return func_ov059_020cd124(GetBoundedEntryField_0206db5c(index));
    }
    return 0;
}
