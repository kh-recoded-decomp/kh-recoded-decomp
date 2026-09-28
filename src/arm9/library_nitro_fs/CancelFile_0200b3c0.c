#include "nitro/types.h"

typedef struct Archive {
    u8 pad_00[0x14];
    u32 flag;
} Archive;

typedef struct File {
    u8 pad_00[8];
    Archive *arc;
    u32 stat;
} File;

extern int func_02004938(void);
extern void func_0200494c(int state);

static inline BOOL IsFileBusy(volatile const File *file)
{
    return (file->stat & 1) ? TRUE : FALSE;
}

void CancelFile_0200b3c0(File *file)
{
    int state = func_02004938();

    if (IsFileBusy(file)) {
        file->stat |= 2;
        file->arc->flag |= 0x20;
    }
    func_0200494c(state);
}
