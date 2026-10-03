#include "nitro/types.h"

typedef struct EnemyRecord {
    u8 kind;
    u8 variant;
    u8 pad_02[6];
    s16 counterAmount;
    u8 pad_0a[2];
} EnemyRecord;

typedef struct EnemyTable {
    u32 unk0;
    EnemyRecord *records;
} EnemyTable;

typedef struct EnemyTableHolder {
    EnemyTable *table;
} EnemyTableHolder;

extern EnemyTableHolder *data_ov001_020a0470;
extern void SpawnDropsPerTenUnits_0206671c(s32 amount, u32 position, u32 kind);
extern int func_ov001_020644b0(void);
extern u32 GetGroupIndexedValue_020bb86c(u8 kind);
extern int func_ov001_02063a38(void);
extern BOOL func_ov035_020bae74(void);
extern BOOL func_ov001_020645c8(u32 flagId);
extern void AddSessionCounter_02063a80(int index, int amount);
extern u8 LookupMappedByteValue_02068530(u32 id);
extern void RollEnemyDrop_0206844c(int level, int recordId, u32 owner, BOOL reduced);
extern void func_0202737c(int messageId, int category, int amount, int limit);
extern void func_ov001_0206e074(u8 enabled);
extern void SetGlobalPackedBit_02027320(u32 bit);

void HandleEnemyDefeat_02068abc(s32 group, s32 index, u32 position, BOOL notify, int level)
{
    EnemyTableHolder *holder = data_ov001_020a0470;
    BOOL dropItem = TRUE;
    BOOL countKill = TRUE;
    EnemyRecord *record;
    int kind;
    int dropId;

    if (group < 0 && index < 0) {
        SpawnDropsPerTenUnits_0206671c(1000, position, 4);
        return;
    }
    record = &holder->table->records[index];
    kind = record->kind;
    if (func_ov001_020644b0() == 900) {
        kind = GetGroupIndexedValue_020bb86c(record->kind);
    }
    if (func_ov001_02063a38() == 6) {
        dropItem = FALSE;
        if (!func_ov035_020bae74()) {
            countKill = FALSE;
        }
    }
    if (func_ov001_020644b0() == 500) {
        if ((kind == 0xb && record->variant != 0) || (kind == 0xc && record->variant != 0)) {
            dropItem = FALSE;
        }
    }
    if (func_ov001_020645c8(0x3631)) {
        dropItem = FALSE;
    }
    if (func_ov001_02063a38() == 4) {
        AddSessionCounter_02063a80(0, record->counterAmount);
    }
    switch (kind) {
    case 0x25:
    case 0x35:
    case 0x38:
    case 0x3b:
        AddSessionCounter_02063a80(0, record->counterAmount);
        break;
    }
    dropId = LookupMappedByteValue_02068530(kind);
    if (dropId == 0x28) {
        dropItem = FALSE;
        countKill = FALSE;
    }
    if (dropItem) {
        RollEnemyDrop_0206844c(level, dropId, position, FALSE);
    }
    if (countKill) {
        func_0202737c(dropId * 0x11 + 0x680, 0x11, 1, 99999);
        func_ov001_0206e074(notify != 0);
    }
    switch (kind) {
    case 0x1a:
        SetGlobalPackedBit_02027320(0xbe5);
        return;
    case 0x3e:
        SetGlobalPackedBit_02027320(0xbe7);
        return;
    case 0x41:
        SetGlobalPackedBit_02027320(0xbe6);
        return;
    }
}
