#include "nitro/types.h"

typedef struct GroupBounds {
    u32 words[3];
} GroupBounds;

typedef struct EventGroup {
    u8 groupId;
    u8 mode : 7;
    u8 latched : 1;
    u16 timer;
    u8 state;
    u8 unknown_05;
    u8 flag;
    u8 eventCount;
    GroupBounds bounds;
    u16 *eventIds;
    u8 unknown_18[4];
} EventGroup;

typedef struct EventRef {
    u8 id;
    u8 unknown_01[3];
} EventRef;

typedef struct EventList {
    u8 count;
    u8 unknown_01[3];
    EventRef *refs;
} EventList;

typedef struct ClipHeader {
    u8 unknown_00[2];
    s8 groupCount;
    u8 unknown_03;
    EventList *events;
    GroupBounds groups[1];
} ClipHeader;

typedef struct EventTable {
    u8 busy;
    u8 unknown_01;
    u8 groupCount;
    u8 unknown_03[7];
    u16 groupSize;
    u8 unknown_0c[4];
    EventGroup *groups;
    int counterA;
    int counterB;
    int counterC;
    u16 timer;
    s8 activeGroup;
    s8 pendingGroup;
    u8 unknown_24[8];
    u8 *eventStates;
} EventTable;

typedef struct SceneWork {
    u8 unknown_00[0x38];
    ClipHeader *header;
    u8 unknown_3c[4];
    EventTable table;
} SceneWork;

extern SceneWork *data_ov035_020bc500;
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void MIi_CpuClearFast(int value, void *dest, u32 size);
extern void MI_CpuFill8(void *dest, int value, u32 size);
extern int AcquireRecordSlot(int slot, int param);
extern BOOL ReleaseRecordSlot(s32 slot);
extern s32 GetShortTableValueOrDefault(s32 index);

void InitEventGroupTable(void) {
    SceneWork *work = data_ov035_020bc500;
    EventTable *table;
    EventList *events;
    int i = 0;

    work->table.busy = 0;
    table = &work->table;
    table->groupCount = work->header->groupCount;
    table->groupSize = 0;
    table->counterA = 0;
    table->counterB = 0;
    table->counterC = 0;
    table->timer = 0;
    table->activeGroup = -1;
    table->pendingGroup = -1;
    table->groupSize = sizeof(EventGroup);
    table->groups = NNS_FndAllocFromDefaultExpHeapEx(table->groupSize * work->table.groupCount, 4);
    MIi_CpuClearFast(0, table->groups, table->groupSize * work->table.groupCount);
    for (; i < work->table.groupCount; i++) {
        EventGroup *group = &table->groups[i];
        group->groupId = i;
        group->mode = 0;
        group->latched = 0;
        group->timer = 0;
        group->state = 0;
        group->flag = 0;
        group->eventCount = 0;
        group->bounds = work->header->groups[i];
        group->eventIds = NULL;
    }
    events = work->header->events;
    AcquireRecordSlot(7, 1);
    table->eventStates = NNSi_FndAllocFromDefaultHeap(events->count);
    MI_CpuFill8(table->eventStates, 0x28, events->count);
    for (i = 0; i < events->count; i++) {
        table->eventStates[i] = GetShortTableValueOrDefault(events->refs[i].id);
    }
    ReleaseRecordSlot(7);
}
