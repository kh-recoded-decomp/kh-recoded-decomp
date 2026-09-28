#include "nitro/types.h"

typedef struct Registration Registration;

typedef struct {
    Registration *id;
    s32 unk_04;
    u32 unk_08;
    s32 unk_0c;
    u32 unk_10;
    void *unk_14;
    u32 unk_18;
} SyncGlobal;

extern SyncGlobal g_syncGlobal_02057b00;
extern u8 data_0205296c[];
extern u8 data_02055c2c[];

extern u16 GetU16Field_020049f0(void);
extern Registration *FindRegisteredEntryByName_0200aa68(void *context, char *name);

void InitSyncGlobal_0200b75c(void) {
    u16 mode = GetU16Field_020049f0();

    if (mode == 2) {
        g_syncGlobal_02057b00.unk_04 = -1;
        g_syncGlobal_02057b00.unk_08 = 0;
        g_syncGlobal_02057b00.unk_0c = -1;
        g_syncGlobal_02057b00.unk_10 = 0;
    } else {
        g_syncGlobal_02057b00.unk_04 = 0;
        g_syncGlobal_02057b00.unk_08 = 0;
        g_syncGlobal_02057b00.unk_0c = 0;
        g_syncGlobal_02057b00.unk_10 = 0;
    }
    g_syncGlobal_02057b00.unk_14 = data_0205296c;
    g_syncGlobal_02057b00.unk_18 = 0x40;
    g_syncGlobal_02057b00.id = FindRegisteredEntryByName_0200aa68(data_02055c2c, (char *)3);
}
