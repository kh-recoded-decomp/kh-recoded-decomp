#include "nitro/types.h"

typedef struct PartyState {
    int mode;
} PartyState;

extern PartyState *data_ov001_020a049c;
extern u32 GetBoundedEntryField_0206db5c(int index);
extern void func_ov052_020ceaf4(u32 entry, int arg);
extern void func_ov059_020cd078(u32 entry, int arg);

void DispatchPartyEntryArgByMode_0206e65c(int index, int arg)
{
    switch (data_ov001_020a049c->mode) {
    case 0:
    case 2:
        func_ov052_020ceaf4(GetBoundedEntryField_0206db5c(index), arg);
        break;
    case 1:
        func_ov059_020cd078(GetBoundedEntryField_0206db5c(index), arg);
        break;
    }
}
