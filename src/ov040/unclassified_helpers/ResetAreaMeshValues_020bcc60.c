#include "nitro/types.h"

typedef struct AreaContext {
    u8 pad_00[0x1c];
    s8 phase;
    u8 pad_1d[0x25];
    u8 meshCount;
} AreaContext;

typedef struct MeshValue {
    u8 bytes[4];
} MeshValue;

typedef struct MenuMachine {
    u8 pad_000[0x13c];
    u16 flags;
} MenuMachine;

extern AreaContext *data_ov035_020bc4e0;
extern MenuMachine *data_ov040_020be260;
extern MeshValue data_ov040_020be1a0;
extern char data_ov040_020be218[];
extern char data_ov040_020be220[];
extern int func_ov001_02063404(void);
extern int OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void SetWorldMeshEntryValueByName_02036368(const char *name, const MeshValue *value);

int ResetAreaMeshValues_020bcc60(void)
{
    AreaContext *context;
    int i;

    if (func_ov001_02063404() == 1 && data_ov035_020bc4e0->phase != 3) {
        data_ov035_020bc4e0->phase = 0;
    }
    i = 0;
    context = data_ov035_020bc4e0;
    if (i < context->meshCount) {
        MeshValue value;
        MeshValue base = data_ov040_020be1a0;

        do {
            char name[16];

            value = base;
            OS_SPrintf_02002428(name, data_ov040_020be218, data_ov040_020be220, i);
            value.bytes[1] = i;
            SetWorldMeshEntryValueByName_02036368(name, &value);
            i++;
        } while (i < context->meshCount);
    }
    data_ov040_020be260->flags |= 0x8000;
    return 1;
}

