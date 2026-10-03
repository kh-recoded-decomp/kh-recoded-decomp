#include "nitro/types.h"

typedef struct ProfileSource {
    u8 key[0x10];
    u16 name[0xb];
    u16 message[0x1b];
    u16 iconId;
    u8 pad_5E[7];
    u8 attrA;
    u8 attrB;
    u8 attrC;
    u8 attrD;
    u8 pad_69[2];
    u8 attrE;
    u8 attrF;
} ProfileSource;

typedef struct ProfileRecord {
    u8 name[0xf];
    u8 message[0x27];
    u16 iconId;
    u32 attrA : 4;
    u32 attrB : 5;
    u32 attrC : 5;
    u32 attrD : 3;
    u32 flag17 : 1;
    u32 flag18 : 1;
    u32 unused19 : 1;
    u32 attrE : 4;
    u32 attrF : 1;
    u32 unused25 : 7;
    u8 key[0x10];
} ProfileRecord;

typedef struct ProfileHistory {
    ProfileRecord records[0x5a];
    u8 pad_1AB8[0x10];
    u32 count : 7;
    u32 rest : 25;
} ProfileHistory;

extern ProfileHistory *func_ov002_02066fe0(void);
extern void func_01ff8830(void *dest, int value, u32 size);
extern void func_01ff89a8(const void *src, void *dst, u32 size);
extern void func_ov002_02065ff4(const u16 *src, int length, u8 *dest, int destSize);
extern void func_ov002_02067170(int index);
extern void func_0202737c(int id, int kind, int delta, int limit);

void AppendProfileHistory_02066ff8(ProfileSource *source)
{
    ProfileHistory *history = func_ov002_02066fe0();
    ProfileRecord record;

    func_01ff8830(&record, 0, sizeof(record));
    func_ov002_02065ff4(source->name, 10, record.name, 0xf);
    func_ov002_02065ff4(source->message, 0x1a, record.message, 0x27);
    record.iconId = source->iconId;
    func_01ff89a8(source->key, record.key, 0x10);
    record.attrC = source->attrC;
    record.attrA = source->attrA;
    record.attrD = source->attrD;
    record.flag17 = 0;
    record.attrB = source->attrB;
    record.flag18 = 0;
    record.attrE = source->attrE;
    if (source->attrF) {
        record.attrF = 1;
    } else {
        record.attrF = 0;
    }
    if (history->count >= 0x5a) {
        func_ov002_02067170(0);
    }
    func_01ff89a8(&record, &history->records[history->count], sizeof(record));
    history->count = history->count + 1;
    func_0202737c(0xb48, 0x11, 1, 99999);
}
