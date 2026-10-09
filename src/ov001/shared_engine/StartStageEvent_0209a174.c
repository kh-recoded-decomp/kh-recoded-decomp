#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s8 kind;
    u8 count;
    u8 pad_02[2];
} EventSide;

typedef struct {
    s8 sideCount;
    s8 layer;
    u8 pad_02[2];
    EventSide sides[1];
} EventGroup;

typedef struct {
    u8 memberBase;
    u8 pad_01[0xb];
} GroupDef;

typedef struct {
    u8 groupIndex;
    u8 pad_01;
    u8 startMode;
    u8 pad_03[5];
    VecFx32 position;
    u8 pad_14[0x1c];
} EventDef;

typedef struct {
    u16 unk_00;
    u16 eventCount;
    GroupDef *groupDefs;
    EventDef *defs;
    EventGroup *groups[1];
} EventTable;

typedef struct {
    u8 pad_00[2];
    u16 state;
    u8 pad_04[5];
    u8 flagsLow : 2;
    u8 startMode : 2;
    u8 loaded : 1;
    u8 flagsHigh : 3;
    u16 firstResource;
    s16 lastResource;
    u8 pad_0E[0x1a];
} StageEventHeader;

typedef struct {
    u8 pad_000[0xe];
    u16 resourceId;
    u8 pad_010[0x1b8];
} StageResource;

typedef struct {
    u16 memberId;
    u8 pad_02[6];
} ActiveMember;

typedef struct {
    u32 flags;
    u8 pad_004[4];
    ActiveMember members[0x40];
    StageEventHeader *headers;
    StageEventHeader **eventHeaders;
    StageResource *resources;
    u8 pad_00214[0x18bd0];
    u16 slotLimit;
    u16 eventCount;
    u16 headerCount;
    u8 pad_18DEA[2];
    u16 memberCount;
    u16 slotsUsed;
    u8 pad_18DF0[8];
    EventTable *eventTable;
} StageManager;

extern StageManager *g_stageManager_020a0508;

extern BOOL Session_Exists_0206c768(void);
extern void RegisterSessionCallback_0206c704(void (*callback)(void));
extern void func_ov001_02099a84(void);
extern u32 RemapGroupMemberId_0209cfcc(u32 memberId, int groupId, BOOL skipLookup);
extern BOOL func_ov001_0209d064(u32 id);
extern void func_ov001_0209a4bc(u32 memberId, u16 eventId, int kind, int arg, int slot, BOOL large);
extern void InitStageEventHeader_020988d4(StageEventHeader *header, u16 type, u16 objectId, u16 actorId, u16 layer, const VecFx32 *position, u16 param);
extern void *LoadStageResource_0209a784(u32 id);
extern int GetSessionModeOrZero_02098714(void);
extern s16 LoadStageModelEntry_0209a8ac(u16 id, int variant, int type);
extern int GetSessionRankValue_020979dc(u32 memberId);
extern void func_ov001_0209ab64(u32 memberId, int rank, int slot);

void StartStageEvent_0209a174(u16 eventId, u16 param) {
    EventTable *table;
    EventDef *def;
    EventGroup *group;
    StageEventHeader *header;
    EventSide *side;
    u16 m;
    u16 i;
    u16 firstSlot;
    u16 n;
    u16 j;
    u16 k;
    u32 memberId;

    if (eventId < g_stageManager_020a0508->eventCount) {
        table = g_stageManager_020a0508->eventTable;

        def = &table->defs[eventId];
        group = table->groups[def->groupIndex];
        if (eventId < table->eventCount) {
            if (Session_Exists_0206c768() && !(g_stageManager_020a0508->flags & 0x80000000)) {
                RegisterSessionCallback_0206c704(func_ov001_02099a84);
                g_stageManager_020a0508->flags |= 0x80000000;
            }
            header = g_stageManager_020a0508->eventHeaders[eventId];
            if (header == NULL) {
                firstSlot = g_stageManager_020a0508->slotsUsed;
                for (i = 0; i < group->sideCount; i++) {
                    side = &group->sides[i];
                    memberId = RemapGroupMemberId_0209cfcc(table->groupDefs[side->kind].memberBase, side->kind, FALSE);
                    for (j = 0; j < side->count; j++) {
                        if (g_stageManager_020a0508->slotsUsed + side->count >= g_stageManager_020a0508->slotLimit) {
                            goto end;
                        }
                        func_ov001_0209a4bc(memberId, eventId + 1, side->kind, 0, 0xffff, func_ov001_0209d064(memberId));
                    }
                }
                header = &g_stageManager_020a0508->headers[g_stageManager_020a0508->headerCount];
                InitStageEventHeader_020988d4(header, eventId, firstSlot, g_stageManager_020a0508->slotsUsed - 1, group->layer, &def->position, param);
                g_stageManager_020a0508->eventHeaders[eventId] = &g_stageManager_020a0508->headers[g_stageManager_020a0508->headerCount];
                g_stageManager_020a0508->headerCount++;
            } else {
                for (k = header->firstResource; k <= header->lastResource; k++) {
                    LoadStageResource_0209a784(g_stageManager_020a0508->resources[k].resourceId);
                }
            }
            header->loaded = TRUE;
            if (header != NULL) {
                if (GetSessionModeOrZero_02098714() == 7) {
                    LoadStageModelEntry_0209a8ac(0, 0, 2);
                }
                if (GetSessionModeOrZero_02098714() == 10) {
                    LoadStageModelEntry_0209a8ac(0x1b, 0, 1);
                }
                LoadStageModelEntry_0209a8ac(0xa, 0, 1);
                LoadStageModelEntry_0209a8ac(0xb, 0, 1);
                LoadStageModelEntry_0209a8ac(0x15, 0, 1);
                LoadStageModelEntry_0209a8ac(1, 0, 1);
                LoadStageModelEntry_0209a8ac(2, 0, 1);
                LoadStageModelEntry_0209a8ac(3, 0, 1);
                LoadStageModelEntry_0209a8ac(5, 0, 1);
                LoadStageModelEntry_0209a8ac(0x2bd, 0, 1);
                LoadStageModelEntry_0209a8ac(0x16, 0, 1);
                LoadStageModelEntry_0209a8ac(0x17, 0, 1);
                LoadStageModelEntry_0209a8ac(0x18, 0, 1);
                LoadStageModelEntry_0209a8ac(0x19, 0, 1);
                LoadStageModelEntry_0209a8ac(0x1c, 0, 1);
                LoadStageModelEntry_0209a8ac(0x11, 0, 1);
                LoadStageModelEntry_0209a8ac(0x14, 0, 1);
                LoadStageModelEntry_0209a8ac(0x10, 0, 1);
                LoadStageModelEntry_0209a8ac(0x1d, 0, 1);
                for (n = 0; n < group->sideCount; n++) {
                    memberId = RemapGroupMemberId_0209cfcc(g_stageManager_020a0508->eventTable->groupDefs[group->sides[n].kind].memberBase, group->sides[n].kind, FALSE);
                    for (m = 0; m < g_stageManager_020a0508->memberCount; m++) {
                        if (memberId == g_stageManager_020a0508->members[m].memberId) {
                            func_ov001_0209ab64(memberId, GetSessionRankValue_020979dc(memberId), 0xffff);
                            break;
                        }
                    }
                }
                if (header->state != 7) {
                    header->startMode = 0;
                    switch (def->startMode) {
                    case 1:
                    case 2:
                        header->startMode = def->startMode;
                        header->state = 6;
                        return;
                    }
                    header->state = 2;
                }
            }
        }
    }
end:
    ;
}
