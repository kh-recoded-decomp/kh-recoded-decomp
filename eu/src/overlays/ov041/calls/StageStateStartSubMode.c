#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"

/* What a task is started with. */
typedef struct StageTaskParams {
    int kind;
    void *heap;
    int argument;
} StageTaskParams;

extern const void *gSubModeTaskDefinition[];
extern void *Heap_GetCurrent(void);
extern void *CreateTaskObject(const void *definition, StageTaskParams *params);
extern void LoadHudLayersAndRecordText(void);
extern int CountAssignedFieldSlots(void);
extern void SetMovieMenuRow(int row);
extern int GetGaugeSlotMaximum(int slot);
extern int GetGaugeSlotCurrent(int slot);
extern void SetChannelRatioLevels(int channel, int maximum, int current);
extern void GetCurrentAreaIndex(void);
extern int GetMovieEntryKind(void);
extern void SetMovieModelAlpha(int kind);
extern void EnterPanelState(int state);
extern void SetStageState(int state, BOOL runNow);

static inline StageTaskParams MakeTaskParams(void *heap)
{
    StageTaskParams params;

    params.kind = 3;
    params.heap = heap;
    params.argument = 0;
    return params;
}

/* Stage state 2: starts the sub-mode task, sets up the HUD, the gauges and the panel, then moves on to state 3. */
void StageStateStartSubMode(void)
{
    StageWork *work = gMovieContextState->stageWork;
    StageTaskParams params = MakeTaskParams(Heap_GetCurrent());
    int slot;

    work->subModeTask = CreateTaskObject(gSubModeTaskDefinition, &params);
    LoadHudLayersAndRecordText();
    SetMovieMenuRow(CountAssignedFieldSlots() + 1);
    for (slot = 0; slot < 3; slot++) {
        SetChannelRatioLevels(slot, GetGaugeSlotMaximum(slot), GetGaugeSlotCurrent(slot));
    }
    GetCurrentAreaIndex();
    SetMovieModelAlpha(GetMovieEntryKind());
    gMovieContextState->flags |= 0xc;
    EnterPanelState(work->panelState);
    SetStageState(3, TRUE);
}
