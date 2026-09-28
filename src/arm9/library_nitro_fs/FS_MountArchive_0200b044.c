#include "nitro/types.h"

struct FSArchive;

typedef struct FSFile {
    struct FSFile *next;
    void *userdata;
    struct FSArchive *arc;
    u32 stat;
    void *argument;
    int error;
    u8 queue[8];
    u8 pad_20[0x28];
} FSFile;

typedef struct FSArchive {
    u32 name;
    struct FSArchive *next;
    FSFile *list;
    u8 queue[8];
    u32 flag;
    u8 pad_18[8];
    void *userdata;
    const void *vtbl;
} FSArchive;

extern void func_0200b394(FSFile *file);
extern int func_0200a2fc(FSFile *file, u32 command);

BOOL FS_MountArchive_0200b044(FSArchive *arc, void *userdata, const void *vtbl, u32 reserved) {
    arc->userdata = userdata;
    arc->vtbl = vtbl;
    {
        FSFile tmp[1];
        func_0200b394(tmp);
        tmp->arc = arc;
        func_0200a2fc(tmp, 0x11);
    }
    arc->flag |= 2;
    return TRUE;
}
