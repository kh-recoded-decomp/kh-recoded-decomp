#include "nitro/types.h"

typedef struct PanelWork {
    u8 pad_0000[0x10];
    u8 archive[0xc90];
    u8 archiveBuffer[0x58];
    u32 resourceTable;
} PanelWork;

typedef struct PanelManager {
    u32 unk_00;
    PanelWork *work;
} PanelManager;

extern PanelManager data_ov036_020c3940;
extern void (*gTextScriptCommandHandlers[])(void);
extern char sOv036_E_020c3744[];

extern void StoreGlobalArrayEntry(int index, void *value);
extern void FormatSessionNumber(int index, char *name);
extern u32 func_ov001_020636e4(void);
extern int findSharedResourceByName(void *table, void *name);
extern int RoundAndInitArchive(void *record, u32 flags, void *flag, void *extra);
extern void SetLoaderCallbacks(void *context, void *writeHandler, void *readHandler);
extern void WriteSessionPackedBits(void);
extern void ReadSessionPackedBits(void);

void InitializePanelArchive(void)
{
    PanelWork *work = data_ov036_020c3940.work;
    u32 table;
    u32 fileId;
    char name[128];

    StoreGlobalArrayEntry(5, gTextScriptCommandHandlers);
    FormatSessionNumber(0, name);
    work->resourceTable = func_ov001_020636e4();
    table = func_ov001_020636e4();
    fileId = ((table + 0x8000) & 0xfffffc) << 7 | 0x80000000 |
             (findSharedResourceByName((void *)func_ov001_020636e4(), name) & 0x1ff);
    RoundAndInitArchive(work->archive, fileId, sOv036_E_020c3744, work->archiveBuffer);
    SetLoaderCallbacks(work->archive, WriteSessionPackedBits, ReadSessionPackedBits);
}
