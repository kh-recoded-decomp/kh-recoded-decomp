#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x648];
    u8 workArea[0x81c - 0x648];
    u8 *resourceTable;
} SessionArchive;

typedef struct {
    u8 pad_0000[0x1f10];
    SessionArchive archive;
} Session;

extern Session *data_ov001_020a0460;
extern void FormatSessionNumber_02063578(int number, char *buffer);
extern u32 findSharedResourceByName_0202cd8c(u8 *table, char *name);
extern int RoundAndInitArchive_020258b0(SessionArchive *archive, u32 flags, int flag, void *extra);
extern void SetLoaderCallbacks_02025914(SessionArchive *archive, void *writeHandler, void *readHandler);
extern void WriteSessionPackedBits_0206459c(void);
extern void ReadSessionPackedBits_02064574(void);

void OpenSessionArchive_020635b0(int number, int flag)
{
    SessionArchive *archive = &data_ov001_020a0460->archive;
    char name[12];
    u32 index;

    FormatSessionNumber_02063578(number, name);
    index = findSharedResourceByName_0202cd8c(archive->resourceTable, name);
    RoundAndInitArchive_020258b0(archive, ((((u32)archive->resourceTable + 0x8000) & 0xfffffc) << 7 | 0x80000000) | (index & 0x1ff), flag, archive->workArea);
    SetLoaderCallbacks_02025914(archive, WriteSessionPackedBits_0206459c, ReadSessionPackedBits_02064574);
}
