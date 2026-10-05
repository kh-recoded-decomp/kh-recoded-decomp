#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u8 count6;
    u8 count7;
    u8 pad_08[0xc];
    u16 *list;
    u8 pad_18[4];
} Group;

typedef struct {
    u8 pad_00[0x10];
    Group *groups;
    u8 pad_14[0x14];
    u16 *buffer;
} GroupTable;

typedef struct {
    u8 pad_00[0x40];
    GroupTable table;
} Manager;

typedef struct {
    u8 pad_00[0x42];
    u8 groupCount;
} ManagerHead;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Position;

typedef struct {
    u8 pad_00[8];
    Position pos;
} LargeEntry;

extern Manager *data_ov035_020bc4e0;
extern int func_ov001_02068984(void);
extern u16 *func_ov001_02068994(int index);
extern LargeEntry *GetLargeTableEntry(u16 id);
extern BOOL func_ov040_020bcc44(int id);
extern int FindActorRewardValue(Position *pos);
extern BOOL StageEvents_CheckEvent(int id);
extern BOOL func_ov001_02087df8(int id);
extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);

void SortObjectsIntoAreaGroups(void) {
    GroupTable *table = &data_ov035_020bc4e0->table;
    int count = func_ov001_02068984();
    int i;
    int offset;
    Group *group;
    u16 *id;
    Position pos;
    u16 ids[32][64];

    for (i = 0; i < count; i++) {
        int groupIndex;
        id = func_ov001_02068994(i);
        pos = GetLargeTableEntry(*id)->pos;
        if (func_ov040_020bcc44(*id) == 0) {
            pos.y += 0x800;
            groupIndex = FindActorRewardValue(&pos);
            group = &table->groups[groupIndex];
            ids[groupIndex][group->count7] = *id;
            group->count7++;
            if (StageEvents_CheckEvent(*id) == 0 && func_ov001_02087df8(*id) == 0) {
                group->count6++;
            }
        }
    }
    offset = 0;
    for (i = 0; i < ((u8 *)data_ov035_020bc4e0)[0x42]; i++) {
        group = &table->groups[i];
        MIi_CpuCopy16(ids[i], table->buffer + offset, group->count7 * 2);
        group->list = table->buffer + offset;
        offset += group->count7;
    }
}
