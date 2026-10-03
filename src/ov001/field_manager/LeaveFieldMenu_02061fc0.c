#include "nitro/types.h"

typedef struct SessionCallbacks {
    u32 pad_00;
    BOOL (*canLeave)(void);
    void (*onLeave)(void);
} SessionCallbacks;

typedef struct SessionState {
    u8 pad_000[0x20a];
    s16 roomEntry;
    u8 pad_20c[6];
    s16 savedEntry;
    u32 flag0 : 1;
    u32 flag1 : 1;
    u32 flag2 : 1;
    u32 formationDirty : 1;
    u32 selectionDirty : 1;
    u32 flag5 : 1;
    u32 flag6 : 1;
    u32 skipRefresh : 1;
    u32 flag8 : 4;
    u32 flag12 : 1;
    u8 pad_218[0x34];
    s16 loadedEntry;
    u8 pad_24e[0x1cbe];
    void *scratch;
    u8 pad_1f10[0x834];
    u8 counters[2];
    u8 pad_2746[0x70];
    u8 panelFlag0 : 1;
    u8 formationType : 2;
    u8 panelFlag3 : 1;
    u8 panelFlag4 : 1;
    u8 pad_27b7;
    u8 formation[0x39];
    u8 promptFlag0 : 1;
    u8 promptMode : 3;
    u8 pad_27f2[0xa];
    s8 partyLeader;
    u8 pad_27fd[0xb];
    s8 menuKind;
    u8 pad_2809[3];
    SessionCallbacks callbacks;
} SessionState;

extern SessionState *data_ov001_020a0460;
extern void func_ov046_020c0e38(void *formation);
extern void Panel_SetFormationType_0207b478(int type);
extern void RefreshSelectionLinkValues_0204fb1c(void);
extern void func_ov001_020645e8(int flag);
extern void func_ov001_02064364(int id);
extern void func_ov001_02068e44(void);
extern void func_ov001_020690c8(void);
extern void func_01ff8830(void *dst, int value, u32 size);
extern int func_ov001_02067ed4(void);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

int LeaveFieldMenu_02061fc0(void)
{
    SessionState *state = data_ov001_020a0460;
    SessionCallbacks *callbacks = &state->callbacks;
    u32 selectionDirty = state->selectionDirty;
    s8 kind;

    if (callbacks->canLeave != NULL && !callbacks->canLeave()) {
        return -1;
    }
    if (callbacks->onLeave != NULL) {
        callbacks->onLeave();
    }
    if (state->formationDirty) {
        func_ov046_020c0e38(state->formation);
        Panel_SetFormationType_0207b478(state->formationType);
    }
    if (state->menuKind == 11 && state->selectionDirty) {
        RefreshSelectionLinkValues_0204fb1c();
    }
    state->panelFlag4 = 0;
    state->panelFlag0 = 0;
    state->flag2 = 0;
    state->formationDirty = 0;
    state->selectionDirty = 0;
    state->flag5 = 0;
    func_ov001_020645e8(0x1a05);
    func_ov001_020645e8(0x1a06);
    if (state->skipRefresh) {
        state->flag12 = 0;
        if (state->menuKind == 11) {
            func_ov001_02064364(3);
        }
        return 5;
    }
    kind = state->menuKind;
    if (kind == 0 || kind == 4 || kind == 6 || kind == 7 || kind == 10) {
        func_ov001_02068e44();
    }
    func_ov001_020690c8();
    func_01ff8830(state->counters, 0, 2);
    state->promptMode = 2;
    if (func_ov001_02067ed4() > 0
        && (selectionDirty
            || (data_ov001_020a0460->roomEntry != data_ov001_020a0460->savedEntry
                && func_ov001_02067ed4() != state->loadedEntry))) {
        func_ov001_02064364(3);
    }
    if (state->scratch != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(state->scratch);
        state->scratch = NULL;
    }
    if (data_ov001_020a0460->partyLeader != -1 && func_ov001_02067ed4() > 0
        && func_ov001_02067ed4() != state->partyLeader) {
        data_ov001_020a0460->partyLeader = -1;
    }
    return 4;
}
