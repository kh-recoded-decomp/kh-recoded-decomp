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
extern MenuMachine *data_ov040_020be280;
extern MeshValue data_ov040_020be1c0;
extern char sOv040_FormatSFormat02d_020be238[];
extern char sOv040_Area_020be240[];
extern int RestoreSessionActors(void);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void SetWorldMeshEntryValueByName(const char *name, const MeshValue *value);

int ResetAreaMeshValues(void)
{
    AreaContext *context;
    int i;

    if (RestoreSessionActors() == 1 && data_ov035_020bc4e0->phase != 3) {
        data_ov035_020bc4e0->phase = 0;
    }
    i = 0;
    context = data_ov035_020bc4e0;
    if (i < context->meshCount) {
        MeshValue value;
        MeshValue base = data_ov040_020be1c0;

        do {
            char name[16];

            value = base;
            OS_SPrintf(name, sOv040_FormatSFormat02d_020be238, sOv040_Area_020be240, i);
            value.bytes[1] = i;
            SetWorldMeshEntryValueByName(name, &value);
            i++;
        } while (i < context->meshCount);
    }
    data_ov040_020be280->flags |= 0x8000;
    return 1;
}
