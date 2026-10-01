#include "nitro/types.h"

typedef struct {
    u32 words[17];
} SetHeader;

typedef struct {
    u32 words[8];
} SetEntry;

typedef struct {
    u8 pad_00[0xc];
    SetHeader *headers;
    u8 pad_10[0xc];
    SetEntry (*entries)[8];
} SetTableData;

typedef struct {
    u8 pad_00[8];
    SetTableData *data;
} SetTableFile;

extern char data_ov001_020a043c[];
extern SetTableFile *func_0202c478(const char *path, u32 flags);
extern void RelocateResourceTable_0208efcc(SetTableFile *table);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);

BOOL LoadResourceSetEntry_0209d1c4(int setIndex, SetHeader *header, SetEntry *entries)
{
    SetTableFile *file = func_0202c478(data_ov001_020a043c, 11);
    u16 i;

    if (file != NULL) {
        SetEntry (*table)[8];
        RelocateResourceTable_0208efcc(file);
        table = file->data->entries;
        *header = file->data->headers[setIndex];
        for (i = 0; i < 8; i++) {
            entries[i] = table[setIndex][i];
        }
        NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
    }
    return TRUE;
}
