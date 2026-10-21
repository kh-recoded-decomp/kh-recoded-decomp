#pragma opt_propagation off
#include "nitro/types.h"

typedef struct FieldSessionArgs {
    s16 stageId;
    u8 pad_02[2];
    u8 sceneKind;
    u8 rankA;
    u8 rankB;
    u8 mode : 2;
    u8 optA : 1;
    u8 optB : 1;
    u8 keepState : 1;
    u8 optD : 1;
    int param;
} FieldSessionArgs;

typedef struct SavedFieldState {
    u8 snapshot[0xcc];
    u8 values[0xc];
    u16 extra;
    u16 slotValueA;
    u16 slotValueB;
    s8 world;
    u8 rank;
    s16 room;
    u8 pad_e2[2];
    void *buffer;
} SavedFieldState;

typedef struct FieldWorkArea {
    u8 pad_000[0xb0];
    u8 snapshot[0xcc];
    u8 pad_17c[0x1e0 - 0x17c];
} FieldWorkArea;

typedef struct FieldSession {
    void *heap;
    u8 pad_04[4];
    void *heapB;
    int overlayId;
    int unk_10;
    int unk_14;
    s8 overlaySlot;
    s8 unk_19;
    u8 pad_1a[2];
    int unk_1c;
    u8 pad_20[4];
    int unk_24;
    FieldWorkArea work;
    u8 pad_208[4];
    s16 roomA;
    s16 roomB;
    s16 exitKind;
    u8 pad_212[2];
    u32 mode : 2;
    u32 optA : 1;
    u32 flag3 : 2;
    u32 optB : 1;
    u32 flag6 : 3;
    u32 hasRoom : 1;
    u32 keepState : 1;
    u32 flag11 : 3;
    u32 optD : 1;
    u32 flag15 : 1;
    u32 difficulty : 2;
    u32 started : 1;
    u8 pad_218[4];
    int param;
    u8 pad_220[0x24a - 0x220];
    s16 loadedEntry;
    u8 pad_24c[0x2740 - 0x24c];
    void *heapA;
    u8 pad_2744[0x27b5 - 0x2744];
    u8 menuFlag;
    u8 pad_27b6[0x27e8 - 0x27b6];
    int partyEntry;
    u8 pad_27ec[4];
    s8 promptSlot;
    u8 promptFlag : 1;
    u8 promptMode : 3;
    s8 promptIndex;
    u8 pad_27f3[0x27fc - 0x27f3];
    s8 partyLeader;
    u8 pad_27fd[3];
    int menuA;
    int menuB;
    s8 menuKind;
    s8 menuPrev;
    u8 pad_280a[0x29b8 - 0x280a];
    SavedFieldState *saved;
} FieldSession;

typedef struct GameState {
    u8 pad_0000[0x28d4];
    s8 world;
    s8 room;
} GameState;

typedef struct SelectionRecord {
    u8 pad_00[2];
    u16 current;
    u16 base;
} SelectionRecord;

extern FieldSession *data_ov001_020a0460;
extern GameState *data_0205fe0c;
extern FieldSessionArgs data_02060850;
extern u8 data_020608c8;
extern int data_02060848;
extern char data_ov001_0209ec04[];
extern char data_ov001_0209f2cc[];
extern char OverlayId104_00000068[];

extern FieldSession *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void SetBrightnessAndSyncMain_02029e7c(int brightness);
extern void SetSecondaryBrightness_02029ed0(int brightness);
extern void func_02029f78(int processor, int overlayId);
extern void func_02029f98(int processor, int overlayId);
extern int func_ov104_020d1fcc(void *callback, int a, int b);
extern int func_ov104_020d1ea0(void *callback, int a, int b);
extern int func_ov104_020d1f54(void *callback, int a, int b);
extern u32 func_ov001_020613e0(void (*callback)(void));
extern void InitSessionRequestFromArgs_02061430(FieldSessionArgs *args);
extern void InitSessionRequestDefaults_020613f8(FieldSessionArgs *args);
extern void func_0202b5d4(void);
extern void func_01ff8740(int value, void *dst, u32 size);
extern void func_01ff89a8(const void *src, void *dst, u32 size);
extern void func_01ff8830(void *dst, int value, u32 size);
extern u32 ReadGlobalPackedBits_02027348(u32 bitOffset, u32 bitCount);
extern void WriteGlobalPackedBits_02027360(u32 bitOffset, u32 bitCount, u32 value);
extern void LoadDifficultyPresetIntoSession_020644d4(void);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_ov001_02064628(void *values, void *extra);
extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern void WriteSessionPackedBits_0206459c(int bitOffset, u32 bitCount, u32 value);
extern void func_ov001_020645dc(int flag);
extern BOOL func_ov001_020645c8(int flag);
extern void *func_0202a754(void);
extern u32 GetSessionStateFlags2Bit_020649b8(void);
extern void ClearItemCountsByGroup_0202987c(int group);
extern void AcquireMapLayout_020506dc(int a, int b);
extern void ComputePlayerStats_02050b30(GameState *state, void *out, BOOL recompute, int scaleParam);
extern void SetupAllSelectionRecords_0204f85c(void);
extern void func_0204fba0(void);
extern void BuildSelectionEntryList_0204f98c(void);
extern void SyncSelectionRecordFromSlotEntry_0204fabc(void);
extern u8 *func_0205125c(void);
extern SelectionRecord *GetOverlaySelectionRecord(unsigned int selectionIndex);
extern void RefreshSelectionLinkValues_0204fb1c(void);
extern void AcquireRecordManager_02051c80(void);
extern void func_0203574c(void);
extern void func_ov001_020674a0(void);
extern void CreateSceneContext_02067438(void);
extern void CreateStageDataAndStart_02068568(int stageId);
extern void Roster_Create_02069090(void);
extern void CreateRootObject_02068d5c(int param);
extern void func_ov001_02068e54(void);
extern void RequestScene11_02068e28(void);
extern void CreateFieldObjectManager_0207ec54(void);
extern void SetOverlayLayerVisible_0207ef40(int visible);
extern void LoadSeqArcIfChanged_0204d5f0(int seqArcNo);
extern void CacheSeqArcStatus_0204e00c(int status);
extern void ResetTrackState_02062cf8(void);
extern void *func_0202a448(void *descriptor, void *userData);
extern void ClearFieldCounters_02064dc8(void);
extern void CreateSubScene9Task_02066e00(void);
extern void InitPanelState_02028810(void);
extern void func_02025438(int value);
extern int func_ov001_02061af4(void);

static inline BOOL IsProbeBFailed(int failCode)
{
    void *callback = func_ov001_020613e0;
    BOOL missing = FALSE;
    if (failCode == func_ov104_020d1ea0(callback, 0, 0)) {
        missing = TRUE;
    }
    return missing;
}

static inline BOOL IsProbeCFailed(int failCode)
{
    void *callback = func_ov001_020613e0;
    BOOL missing = FALSE;
    if (failCode == func_ov104_020d1f54(callback, 0, 0)) {
        missing = TRUE;
    }
    return missing;
}

void *StartFieldSession_02061468(FieldSessionArgs *args)
{
    FieldSession *session = NNSi_FndGetCurrentRootHeap_0202a764();
    BOOL fresh;
    void (*initRequest)(FieldSessionArgs *);
    BOOL missingA;
    int failCode;
    u8 stats[16];

    data_ov001_020a0460 = session;
    fresh = FALSE;
    SetBrightnessAndSyncMain_02029e7c(-16);
    SetSecondaryBrightness_02029ed0(-16);
    func_02029f78(0, (int)OverlayId104_00000068);
    failCode = ~fresh; /* fresh is still FALSE, so this is -1 */
    missingA = failCode == func_ov104_020d1fcc(func_ov001_020613e0, 0, 0);
    if (missingA) {
        initRequest = InitSessionRequestFromArgs_02061430;
    }
    if (IsProbeBFailed(failCode)) {
        initRequest = InitSessionRequestDefaults_020613f8;
    }
    if (!IsProbeCFailed(failCode)) {
        initRequest = InitSessionRequestDefaults_020613f8;
    }
    func_02029f98(0, (int)OverlayId104_00000068);
    func_0202b5d4();
    if (args == NULL) {
        args = &data_02060850;
    }
    func_01ff8740(0, session, sizeof(FieldSession));
    if (ReadGlobalPackedBits_02027348(0x1a00, 2) != 3) {
        session->difficulty = ReadGlobalPackedBits_02027348(0x1a00, 2);
    }
    WriteGlobalPackedBits_02027360(0x1a00, 2, args->mode);
    LoadDifficultyPresetIntoSession_020644d4();
    if (args->stageId == 900) {
        u32 difficulty = session->difficulty;
        SavedFieldState *saved = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(SavedFieldState));
        int slotBase;

        func_01ff89a8((u8 *)&session->work + 0xb0, saved, sizeof(saved->snapshot));
        func_ov001_02064628(saved->values, &saved->extra);
        slotBase = difficulty * 0xf00;
        saved->slotValueA = ReadGlobalPackedBits_02027348(slotBase + 0x330b, 10);
        saved->slotValueB = ReadGlobalPackedBits_02027348(slotBase + 0x3315, 10);
        saved->rank = ReadSessionPackedBits_02064574(0x360d, 7);
        if (args->keepState) {
            saved->world = data_0205fe0c->world;
            saved->room = data_0205fe0c->room;
            saved->buffer = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(FieldWorkArea));
            func_01ff89a8(&session->work, saved->buffer, sizeof(FieldWorkArea));
            func_01ff8740(0, &session->work, sizeof(FieldWorkArea));
            func_ov001_020645dc(0x3536);
        }
        func_01ff8830((u8 *)&session->work + 0xb0, 0, sizeof(saved->snapshot));
        session->saved = saved;
        WriteSessionPackedBits_0206459c(0x360d, 7, 0);
    }
    session->heap = func_0202a754();
    session->unk_24 = -1;
    session->exitKind = -1;
    session->overlayId = -1;
    session->unk_10 = -1;
    session->unk_14 = -1;
    session->overlaySlot = -1;
    session->unk_19 = -1;
    initRequest(args);
    if (session->roomB > 0) {
        session->hasRoom = 1;
    }
    session->param = args->param;
    session->optA = args->optA;
    session->optB = args->optB;
    session->keepState = args->keepState;
    session->optD = args->optD;
    session->mode = args->mode;
    if (args->stageId < 1000) {
        int world;
        if (args->stageId != 900) {
            world = args->stageId / 100 - 1;
        } else {
            if (!args->keepState) {
                goto skipWorld;
            }
            world = 8;
        }
        data_0205fe0c->world = world;
    }
skipWorld:
    if (args->optA || args->optB) {
        func_ov001_020645dc(0x1a05);
    }
    if (!func_ov001_020645c8(0x1a05) && args->stageId != 900 && args->stageId != 899) {
        if (args->sceneKind != 5) {
            func_01ff8740(0, &session->work, sizeof(FieldWorkArea));
        }
        func_ov001_020645dc(0x3536);
        func_ov001_020645dc(0x35c9);
        func_ov001_020645dc(0x35ca);
        WriteSessionPackedBits_0206459c(0x35c7, 2, GetSessionStateFlags2Bit_020649b8());
        WriteSessionPackedBits_0206459c(0x3633, 2, GetSessionStateFlags2Bit_020649b8());
        WriteSessionPackedBits_0206459c(0x3300, 8, args->rankA);
        WriteSessionPackedBits_0206459c(0x361d, 8, args->rankB);
        fresh = TRUE;
        if (args->mode == 1) {
            ClearItemCountsByGroup_0202987c(data_0205fe0c->world);
        }
    }
    if (ReadGlobalPackedBits_02027348(0x1a00, 2) != 3 && !session->keepState) {
        if (GetSessionStateFlags2Bit_020649b8() < ReadSessionPackedBits_02064574(0x35c7, 2)) {
            WriteSessionPackedBits_0206459c(0x35c7, 2, GetSessionStateFlags2Bit_020649b8());
        }
        if (ReadGlobalPackedBits_02027348(0x1a00, 2) != 2 && data_0205fe0c->world == 3 && args->stageId == 400) {
            s8 roomDelta = data_0205fe0c->room - 0x1d;
            if ((u8)roomDelta <= 1) {
                WriteSessionPackedBits_0206459c(0x3633, 2, GetSessionStateFlags2Bit_020649b8());
            } else if (GetSessionStateFlags2Bit_020649b8() < ReadSessionPackedBits_02064574(0x3633, 2)) {
                WriteSessionPackedBits_0206459c(0x3633, 2, GetSessionStateFlags2Bit_020649b8());
            }
        }
    }
    WriteSessionPackedBits_0206459c(0x330b, 10, session->roomA);
    WriteSessionPackedBits_0206459c(0x3315, 10, session->roomB);
    if (args->sceneKind != 5) {
        AcquireMapLayout_020506dc(1, 1);
        ComputePlayerStats_02050b30(data_0205fe0c, stats, 1, 1);
        SetupAllSelectionRecords_0204f85c();
        func_0204fba0();
        BuildSelectionEntryList_0204f98c();
        SyncSelectionRecordFromSlotEntry_0204fabc();
        if (!func_ov001_020645c8(0x1a05) && args->stageId != 900 && args->stageId != 899) {
            WriteSessionPackedBits_0206459c(0x35cb, 7, func_0205125c()[1]);
        }
        if (ReadGlobalPackedBits_02027348(0x1a00, 2) != 3 && !session->keepState) {
            if (ReadSessionPackedBits_02064574(0x35cb, 7) < func_0205125c()[1]) {
                WriteSessionPackedBits_0206459c(0x35cb, 7, func_0205125c()[1]);
            }
        }
    }
    if (func_ov001_020645c8(0x1a05) || fresh) {
        int i;
        i = 0;
        do {
            GetOverlaySelectionRecord(i)->current = GetOverlaySelectionRecord(i)->base;
        } while (++i < 3);
        RefreshSelectionLinkValues_0204fb1c();
    }
    AcquireRecordManager_02051c80();
    session->menuA = -1;
    session->menuB = -1;
    session->menuKind = -1;
    session->menuPrev = -2;
    session->loadedEntry = -1;
    func_0203574c();
    func_ov001_020674a0();
    CreateSceneContext_02067438();
    CreateStageDataAndStart_02068568(args->stageId);
    Roster_Create_02069090();
    if (args->mode != 3) {
        CreateRootObject_02068d5c(ReadSessionPackedBits_02064574(0x35d2, 0x11) * 1000);
    } else {
        CreateRootObject_02068d5c(0);
    }
    func_ov001_02068e54();
    RequestScene11_02068e28();
    CreateFieldObjectManager_0207ec54();
    SetOverlayLayerVisible_0207ef40(1);
    LoadSeqArcIfChanged_0204d5f0(0);
    CacheSeqArcStatus_0204e00c(1);
    ResetTrackState_02062cf8();
    data_ov001_020a0460->partyLeader = -1;
    session->partyEntry = -1;
    session->promptSlot = -1;
    session->promptIndex = -1;
    session->promptMode = 2;
    data_020608c8 = 1;
    session->heapA = func_0202a448(data_ov001_0209ec04, NULL);
    ClearFieldCounters_02064dc8();
    data_ov001_020a0460->menuFlag = 0;
    CreateSubScene9Task_02066e00();
    InitPanelState_02028810();
    func_02025438(1);
    session->heapB = func_0202a448(data_ov001_0209f2cc, NULL);
    func_01ff8830(&data_02060850, 0, 0xc);
    session->unk_1c = 0;
    data_ov001_020a0460->started = 1;
    data_02060848 = 0;
    return func_ov001_02061af4;
}
