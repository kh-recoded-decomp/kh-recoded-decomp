#include "nitro/types.h"

typedef struct SessionScript {
    u8 pad_000[0x81c];
    u8 *archive;
    u8 pad_820[0xc];
    void *resource;
} SessionScript;

typedef struct Session {
    u8 pad_0000[0x1f10];
    SessionScript script;
} Session;

extern Session *data_ov001_020a0460;
extern char data_ov001_0209e6dc[];
extern int findSharedResourceByName_0202cd8c(unsigned char *table, void *name);
extern void *func_0202c478(u32 fileId, u32 heapId);

void LoadSessionArchiveResource_02062e30(void) {
    SessionScript *script = &data_ov001_020a0460->script;
    int index = findSharedResourceByName_0202cd8c(script->archive, data_ov001_0209e6dc);
    script->resource = func_0202c478(
        ((((u32)(script->archive + 0x8000) & 0xfffffc) << 7) | 0x80000000) | (index & 0x1ff), 2);
}
