#include "nitro/types.h"

typedef struct {
    void *resource;
    void *splitCallback;
    u32 unk_08;
} FieldFont;

typedef struct {
    u8 pad_00[0x78];
    FieldFont fonts[4];
} FieldManager;

typedef struct {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04a4;

FieldFont *GetFieldFont1_020711c8(void)
{
    return &data_ov001_020a04a4.manager->fonts[1];
}
