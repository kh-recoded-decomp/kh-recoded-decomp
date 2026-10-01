#include "nitro/types.h"

typedef struct PanelWork {
    u8 pad_00[0x658];
    u8 archive[0x81c];
    u8 archiveBuffer[0x1d4];
    u32 resourceTable;
} PanelWork;

typedef struct PanelManager {
    u32 unk_00;
    PanelWork *work;
} PanelManager;

extern PanelManager data_ov036_020c3920;
extern const char data_ov036_020c3728[];
extern s8 GetCtxModeByte_02068084(void);
extern void *OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern u32 Msg_OpenContainerAndReadHeader_0202cc6c(const char *path, int mode, int flags);
extern int findSharedResourceByName_0202cd8c(void *table, void *name);
extern int RoundAndInitArchive_020258b0(void *record, u32 flags, void *flag, void *extra);
extern void SetLoaderCallbacks_02025914(void *context, void *writeHandler, void *readHandler);
extern void func_ov001_0206459d(void);
extern void func_ov001_02064575(void);

void func_ov036_020ba820(char *name)
{
    PanelWork *work = data_ov036_020c3920.work;
    int resourceIndex;
    char path[16];

    if (work->resourceTable == 0) {
        OS_SPrintf_02002428(path, data_ov036_020c3728, GetCtxModeByte_02068084() + 1);
        work->resourceTable = Msg_OpenContainerAndReadHeader_0202cc6c(path, 0xd, 0);
    }
    resourceIndex = findSharedResourceByName_0202cd8c((void *)work->resourceTable, name);
    RoundAndInitArchive_020258b0(work->archive,
                                 ((work->resourceTable + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (resourceIndex & 0x1ff),
                                 NULL, work->archiveBuffer);
    SetLoaderCallbacks_02025914(work->archive, func_ov001_0206459d, func_ov001_02064575);
}
