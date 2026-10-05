#include "nitro/types.h"

typedef struct {
    s32 target;
    s32 from;
    s32 to;
} RecordCue;

typedef struct {
    u8 pad_00[0x14];
    u32 position;
    RecordCue cue;
    s32 layoutStep;
    u8 pad_28[0x14];
} ActiveRecord;

typedef struct {
    u8 pad_00[0x28];
    u32 position;
    u8 pad_2c[0xc];
    u32 unk_38;
    u8 pad_3c[0x8];
    s32 recordIndex;
    s32 nextRecordIndex;
    u8 pad_4c[0x4];
    ActiveRecord *records;
    u8 pad_54[0x5c];
    u32 layoutCounter;
    u8 pad_b4[0xc];
    u32 cueFlag;
    s32 cueFrom;
    s32 cueTo;
    s32 directCue;
    s32 cueTarget;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern void func_ov031_020bb6f0(void);
extern void func_ov031_020bbb88(void);
extern void RestoreActiveRecordItems_020bbc84(void);
extern void func_ov031_020bbce8(void);
extern s32 func_ov001_02063a4c(void);
extern void SetFields30And34_020bc008(u32 a, u32 b);
extern void ResetCameraUp_020bca50(s32 angle);
extern void StartSlotLayoutAnimation_0207d3d8(int slot, u16 step);
extern void func_ov001_0207d440(int value);

static inline void ApplyRecordCue(RecordCue *cue)
{
    if (cue->target != 0x7fffffff) {
        if (cue->from != 0x7fffffff && cue->from != 0) {
            g_activeState_020bc800->cueFlag = 0;
            g_activeState_020bc800->cueFrom = cue->from;
            g_activeState_020bc800->cueTo = cue->to;
            g_activeState_020bc800->cueTarget = cue->target;
        } else {
            ResetCameraUp_020bca50(cue->target);
            g_activeState_020bc800->directCue = cue->target;
        }
    }
}

void BeginNextRecord_020bb62c(void)
{
    ActiveRecord *record;

    g_activeState_020bc800->recordIndex = g_activeState_020bc800->nextRecordIndex;
    g_activeState_020bc800->nextRecordIndex = -1;
    g_activeState_020bc800->unk_38 = 0;
    func_ov031_020bb6f0();
    func_ov031_020bbb88();
    RestoreActiveRecordItems_020bbc84();
    func_ov031_020bbce8();
    record = &g_activeState_020bc800->records[g_activeState_020bc800->recordIndex];
    if (func_ov001_02063a4c() == 4) {
        if (g_activeState_020bc800->position != record->position) {
            SetFields30And34_020bc008(record->position, 0x52);
        }
        ApplyRecordCue(&record->cue);
    }
    if (record->layoutStep != 0) {
        g_activeState_020bc800->layoutCounter++;
        StartSlotLayoutAnimation_0207d3d8(3, g_activeState_020bc800->layoutCounter);
        func_ov001_0207d440(1);
    }
}
