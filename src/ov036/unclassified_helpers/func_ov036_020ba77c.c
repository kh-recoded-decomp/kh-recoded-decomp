#include "nitro/types.h"

typedef struct PanelWork {
    u8 pad_00[0x10];
    u8 archive[0xc90];
    u8 archiveBuffer[0x58];
    u32 resourceTable;
} PanelWork;

typedef struct PanelManager {
    u32 unk_00;
    PanelWork *work;
} PanelManager;

extern PanelManager data_ov036_020c3920;
extern u8 data_ov036_020c373c[];
extern u8 data_ov036_020c3724[];
extern void StoreGlobalArrayEntry_02025668(int index, void *value);
extern void func_ov001_02063578(int index, char *name);
extern u32 func_ov001_020636e4(void);
extern int findSharedResourceByName_0202cd8c(void *table, void *name);
extern int RoundAndInitArchive_020258b0(void *record, u32 flags, void *flag, void *extra);
extern void SetLoaderCallbacks_02025914(void *context, void *writeHandler, void *readHandler);
extern void func_ov001_0206459d(void);
extern void func_ov001_02064575(void);

void func_ov036_020ba77c(void)
{
    PanelWork *work = data_ov036_020c3920.work;
    u32 table;
    u32 fileId;
    char name[128];

    StoreGlobalArrayEntry_02025668(5, data_ov036_020c373c);
    func_ov001_02063578(0, name);
    work->resourceTable = func_ov001_020636e4();
    table = func_ov001_020636e4();
    fileId = ((table + 0x8000) & 0xfffffc) << 7 | 0x80000000 |
             (findSharedResourceByName_0202cd8c((void *)func_ov001_020636e4(), name) & 0x1ff);
    RoundAndInitArchive_020258b0(work->archive, fileId, data_ov036_020c3724, work->archiveBuffer);
    SetLoaderCallbacks_02025914(work->archive, func_ov001_0206459d, func_ov001_02064575);
}
