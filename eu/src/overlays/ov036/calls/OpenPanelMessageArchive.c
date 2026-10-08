#include "nitro/types.h"

typedef struct PanelMessageArchiveWork {
    u8 pad_0000[0x658];
    u8 archive[0x81c];
    u8 archiveBuffer[0x1d4];
    u32 resourceTable;
} PanelMessageArchiveWork;

typedef struct PanelManager {
    u32 unk_00;
    PanelMessageArchiveWork *work;
} PanelManager;

extern PanelManager data_ov036_020c3940;
extern const char sOv036_Ev2DEVW0FormatDP2_020c3748[];

extern s8 func_ov001_02068084(void);
extern void *OS_SPrintf(char *dst, const char *format, ...);
extern u32 Msg_OpenContainerAndReadHeader(const char *path, int mode, int flags);
extern int findSharedResourceByName(void *table, void *name);
extern int RoundAndInitArchive(void *record, u32 flags, void *flag, void *extra);
extern void SetLoaderCallbacks(void *context, void *writeHandler, void *readHandler);
extern void WriteSessionPackedBits(void);
extern void ReadSessionPackedBits(void);

void OpenPanelMessageArchive(char *name)
{
    PanelMessageArchiveWork *work = data_ov036_020c3940.work;
    int resourceIndex;
    char path[16];

    if (work->resourceTable == 0) {
        OS_SPrintf(path, sOv036_Ev2DEVW0FormatDP2_020c3748, func_ov001_02068084() + 1);
        work->resourceTable = Msg_OpenContainerAndReadHeader(path, 0xd, 0);
    }
    resourceIndex = findSharedResourceByName((void *)work->resourceTable, name);
    RoundAndInitArchive(work->archive,
                        ((work->resourceTable + 0x8000) & 0xfffffc) << 7 |
                            0x80000000 | (resourceIndex & 0x1ff),
                        NULL, work->archiveBuffer);
    SetLoaderCallbacks(work->archive, WriteSessionPackedBits, ReadSessionPackedBits);
}
