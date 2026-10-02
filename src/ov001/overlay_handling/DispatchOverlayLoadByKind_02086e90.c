#include "nitro/types.h"

typedef struct {
    u16 id : 10;
    u16 kind : 6;
    u16 pad;
    void *handle;
} SlotEntry;

typedef struct {
    u8 pad[0x138];
    SlotEntry slots[1];
} SlotTable;

typedef struct {
    u8 pad[0x214];
    u32 unk0 : 4;
    u32 busy : 1;
} FlagBlock;

extern SlotTable *data_ov001_020a04dc;
extern FlagBlock *data_ov001_020a0460;
extern BOOL func_ov001_020645c8(u32 value);
extern int func_ov020_020a31f4(u16 id, int arg);
extern int func_ov020_020a26b4(u16 id, int arg);
extern int func_ov020_020a3940(u16 id, int arg);
extern int func_ov017_020a3a28(u16 id, int arg);
extern int func_ov017_020a3284(u16 id, int arg, void *handle);
extern int func_ov018_020a3198(u16 id, int arg);
extern int func_ov017_020a5b48(u16 id, int arg);
extern int func_ov017_020a2a40(u16 id, int arg);
extern int func_ov016_020a60dc(u16 id, int arg, void *handle);

int DispatchOverlayLoadByKind_02086e90(u32 kind, int slot, u32 id, int arg) {
    SlotTable *table = data_ov001_020a04dc;
    int result = 0;
    void *handle = NULL;
    if (!func_ov001_020645c8(0x3614) && !data_ov001_020a0460->busy) {
        void *found = table->slots[slot].handle;
        if (found != NULL && id == table->slots[slot].id && kind == table->slots[slot].kind) {
            handle = found;
        }
    }
    switch (kind) {
    case 1: result = func_ov020_020a31f4(id, arg); break;
    case 2: result = func_ov020_020a26b4(id, arg); break;
    case 3: result = func_ov020_020a3940(id, arg); break;
    case 4: result = func_ov017_020a3a28(id, arg); break;
    case 5: result = func_ov017_020a3284(id, arg, handle); break;
    case 6: result = func_ov018_020a3198(id, arg); break;
    case 7: result = func_ov017_020a5b48(id, arg); break;
    case 8: result = func_ov017_020a2a40(id, arg); break;
    case 9: result = func_ov016_020a60dc(id, arg, handle); break;
    }
    return result;
}
