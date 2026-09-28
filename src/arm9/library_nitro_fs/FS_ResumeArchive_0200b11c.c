#include "nitro/types.h"

struct FSArchive;

typedef struct FSFile {
    struct FSFile *next;
    void *userdata;
    struct FSArchive *arc;
    u32 stat;
} FSFile;

typedef struct FSArchive {
    u32 name;
    struct FSArchive *next;
    FSFile *list;
    u8 queue[8];
    u32 flag;
} FSArchive;

extern u32 func_02004938(void);
extern void func_0200494c(u32 state);
extern FSFile *func_0200a67c(FSArchive *arc, BOOL owner);
extern void func_0200a828(FSFile *file);

static inline BOOL IsArchiveSuspended(volatile const FSArchive *arc) {
    return (arc->flag & 8) ? TRUE : FALSE;
}

BOOL FS_ResumeArchive_0200b11c(FSArchive *arc) {
    BOOL result;
    {
        u32 savedState = func_02004938();
        result = !IsArchiveSuspended(arc);
        if (!result) {
            arc->flag &= ~8;
        }
        func_0200494c(savedState);
    }
    {
        FSFile *file = func_0200a67c(arc, TRUE);
        if (file) {
            func_0200a828(file);
        }
    }
    return result;
}
