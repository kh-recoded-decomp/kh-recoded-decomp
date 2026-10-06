#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x68];
    u32 unk_68;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04d0;

u32 func_ov001_02077bcc(void)
{
    return data_ov001_020a04d0.menu->unk_68;
}
