#include "nitro/types.h"

typedef struct LevelEntry {
    u8 id;
    u8 pad_01[0xb];
} LevelEntry;

typedef struct LevelTableFile {
    u8 entryCount;
    u8 sectionCount;
    u8 pad_02[2];
    LevelEntry *entries;
    void *data;
    void *sections[1];
} LevelTableFile;

typedef struct LevelTableHolder {
    LevelTableFile *file;
} LevelTableHolder;

extern LevelTableHolder *data_ov001_020a0470;
extern char data_ov001_0209eaac[];
extern u8 *func_ov001_020636e4(void);
extern int findSharedResourceByName_0202cd8c(void *table, void *name);
extern LevelTableFile *func_0202c478(u32 fileId, u32 flags);
extern int func_ov001_020644b0(void);
extern void func_ov001_02068604(u16 *ids, int count);
extern void func_ov001_020876b0(LevelTableFile *file);

static inline BOOL IsMode900(void)
{
    if (func_ov001_020644b0() == 900) {
        return TRUE;
    }
    return FALSE;
}

void LoadLevelTableFile_020686d4(void)
{
    LevelTableHolder *holder = data_ov001_020a0470;
    u8 *container;
    LevelTableFile *file;
    int i;
    int count;
    u16 ids[64];

    container = func_ov001_020636e4();
    file = func_0202c478((findSharedResourceByName_0202cd8c(func_ov001_020636e4(), data_ov001_0209eaac) & 0x1ff)
                             | ((((u32)container + 0x8000) & 0xfffffc) << 7 | 0x80000000),
                         2);
    holder->file = file;
    file->entries = (LevelEntry *)((u8 *)file->entries + (u32)file);
    file->data = (u8 *)file->data + (u32)file;
    for (i = 0; i < file->sectionCount; i++) {
        file->sections[i] = (u8 *)file + (u32)file->sections[i];
    }
    if (!IsMode900()) {
        file = holder->file;
        count = 0;
        for (i = 0; i < file->entryCount; i++) {
            ids[i] = file->entries[i].id;
            count++;
        }
        func_ov001_02068604(ids, count);
    }
    if (holder->file->entryCount != 0) {
        func_ov001_020876b0(holder->file);
    }
}
