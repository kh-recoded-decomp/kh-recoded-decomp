#include "nitro/types.h"

typedef struct EntryPair {
    u16 first;
    u16 second;
} EntryPair;

typedef struct EntryList {
    u8 pad_00[8];
    EntryPair entries[64];
    u8 count;
} EntryList;

typedef struct Session {
    u8 pad_000[0x20a];
    s16 unk_20A;
    u8 pad_20c[6];
    s16 unk_212;
    u32 unk_214_0 : 3;
    u32 suppressRefresh : 1;
    u32 forceRefresh : 1;
} Session;

extern EntryList *data_ov001_020a0470;
extern Session *data_ov001_020a0460;
extern s32 func_ov001_02063a38(void);
extern void func_ov001_020876cc(void);
extern void func_ov001_020876e4(u16 first, u16 second);

void func_ov001_020687b8(void)
{
    EntryList *list = data_ov001_020a0470;
    int index;

    if (func_ov001_02063a38() != 10) {
        Session *session = data_ov001_020a0460;
        if (!session->suppressRefresh) {
            if (session->forceRefresh || session->unk_20A != session->unk_212) {
                func_ov001_020876cc();
            }
        }
    }
    for (index = 0; index < list->count; index++) {
        func_ov001_020876e4(list->entries[index].first, list->entries[index].second);
    }
}
