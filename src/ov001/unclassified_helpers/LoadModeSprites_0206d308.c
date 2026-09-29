#include "nitro/types.h"

typedef struct SpriteLoadDesc {
    const char *name;
    u32 cellFile;
    s32 count;
    u32 charFile;
    u32 param;
} SpriteLoadDesc;

typedef struct SpriteFileEntry {
    u32 fileIndex;
    u32 param;
    s32 count;
} SpriteFileEntry;

typedef struct SpriteNameEntry {
    const char *name;
    u32 param;
    s32 count;
} SpriteNameEntry;

typedef struct SpriteFileTable5 {
    SpriteFileEntry entries[5];
} SpriteFileTable5;

typedef struct SpriteFileTable4 {
    SpriteFileEntry entries[4];
} SpriteFileTable4;

typedef struct SpriteFileTable2 {
    SpriteFileEntry entries[2];
} SpriteFileTable2;

typedef struct MenuSpriteState {
    u8 pad_00[0xa0];
    s16 spriteIds[10];
} MenuSpriteState;

extern MenuSpriteState *data_ov001_020a049c;
extern u8 data_020608c8;
extern SpriteFileTable5 data_ov001_0209db50;
extern SpriteNameEntry data_ov001_0209dabc;
extern char data_ov001_0209ec3c[];
extern SpriteFileTable4 data_ov001_0209db20;
extern SpriteFileTable2 data_ov001_0209dad4;
extern SpriteFileEntry data_ov001_0209dac8;

extern void ZeroBytes0x14_020a8adc(void *obj);
extern s16 func_ov021_020a89a8(SpriteLoadDesc *desc);
extern u32 func_ov001_0206dba0(u32 index);
extern s32 func_ov001_02063a38(void);
extern char *Msg_BuildLangPath_0202b798(const char *src);
extern void *OS_SPrintf_02002428(char *dst, const char *fmt, ...);

#define SPRITE_FILE(archive, index) \
    ((((archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | ((index) & 0x1ff))

void LoadModeSprites_0206d308(void)
{
    MenuSpriteState *state = data_ov001_020a049c;
    SpriteLoadDesc desc;
    SpriteFileTable5 table;
    SpriteNameEntry nameEntry;
    char path[128];
    int i;

    ZeroBytes0x14_020a8adc(&desc);
    table = data_ov001_0209db50;
    for (i = 0; i < 5; i++) {
        SpriteFileEntry *entry;
        u32 fileIndex;
        if (i == 2 && data_020608c8 > 1) {
            continue;
        }
        ZeroBytes0x14_020a8adc(&desc);
        entry = &table.entries[i];
        fileIndex = entry->fileIndex;
        desc.charFile = SPRITE_FILE(func_ov001_0206dba0(2), fileIndex);
        desc.cellFile = SPRITE_FILE(func_ov001_0206dba0(2), fileIndex + 1);
        desc.count = entry->count;
        desc.param = entry->param;
        state->spriteIds[i] = func_ov021_020a89a8(&desc);
    }

    nameEntry = data_ov001_0209dabc;
    OS_SPrintf_02002428(path, data_ov001_0209ec3c, Msg_BuildLangPath_0202b798(nameEntry.name));
    ZeroBytes0x14_020a8adc(&desc);
    desc.cellFile = 1;
    desc.name = path;
    desc.count = nameEntry.count;
    desc.param = nameEntry.param;
    state->spriteIds[5] = func_ov021_020a89a8(&desc);

    switch (func_ov001_02063a38()) {
    case 0:
    case 10: {
        SpriteFileTable4 table4 = data_ov001_0209db20;
        ZeroBytes0x14_020a8adc(&desc);
        desc.charFile = SPRITE_FILE(func_ov001_0206dba0(2), table4.entries[0].fileIndex);
        desc.cellFile = SPRITE_FILE(func_ov001_0206dba0(2), table4.entries[0].fileIndex + 1);
        desc.count = table4.entries[0].count;
        desc.param = table4.entries[0].param;
        state->spriteIds[6] = func_ov021_020a89a8(&desc);
        if (data_020608c8 > 1) {
            for (i = 0; i < 3; i++) {
                u32 fileIndex;
                ZeroBytes0x14_020a8adc(&desc);
                fileIndex = table4.entries[i + 1].fileIndex;
                desc.charFile = SPRITE_FILE(func_ov001_0206dba0(2), fileIndex);
                desc.cellFile = SPRITE_FILE(func_ov001_0206dba0(2), fileIndex + 1);
                desc.count = table4.entries[i + 1].count;
                desc.param = table4.entries[i + 1].param;
                state->spriteIds[7 + i] = func_ov021_020a89a8(&desc);
            }
        }
        break;
    }
    case 4: {
        SpriteFileTable2 table2 = data_ov001_0209dad4;
        for (i = 0; i < 2; i++) {
            SpriteFileEntry *entry;
            u32 fileIndex;
            ZeroBytes0x14_020a8adc(&desc);
            entry = &table2.entries[i];
            fileIndex = entry->fileIndex;
            desc.charFile = SPRITE_FILE(func_ov001_0206dba0(2), fileIndex);
            desc.cellFile = SPRITE_FILE(func_ov001_0206dba0(2), fileIndex + 1);
            desc.count = entry->count;
            desc.param = entry->param;
            state->spriteIds[6 + i] = func_ov021_020a89a8(&desc);
        }
        break;
    }
    case 6: {
        SpriteFileEntry single = data_ov001_0209dac8;
        ZeroBytes0x14_020a8adc(&desc);
        desc.charFile = SPRITE_FILE(func_ov001_0206dba0(2), single.fileIndex);
        desc.cellFile = SPRITE_FILE(func_ov001_0206dba0(2), single.fileIndex + 1);
        desc.count = single.count;
        desc.param = single.param;
        state->spriteIds[6] = func_ov021_020a89a8(&desc);
        break;
    }
    }
}
