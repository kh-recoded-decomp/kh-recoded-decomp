#include "nitro/types.h"
#include "src/overlays/ov001/HudGaugeTable.h"

typedef struct SceneRecord {
    u16 id;
    s16 originX;
    s16 originY;
    u16 width;
    u16 height;
    s16 offsetX;
    s16 offsetY;
    u16 reserved0e;
    s32 userData;
    s32 active;
    u32 attributes;
    u8 reserved1c[0x1c];
} SceneRecord;

typedef struct GaugeState {
    u8 reserved00[0x44];
    s32 rowCount;
    u8 reserved48[0x144 - 0x48];
    SceneRecord *markerTemplates[5];
} GaugeState;

typedef struct SceneTagTracker SceneTagTracker;

#define GAUGE_OFFSET(type, member) ((u32)&((type *)0)->member)
typedef char GaugeSceneRecordSizeCheck[sizeof(SceneRecord) == 0x38 ? 1 : -1];
typedef char GaugeStateSizeCheck[sizeof(GaugeState) == 0x158 ? 1 : -1];
typedef char GaugeRowCountOffsetCheck[GAUGE_OFFSET(GaugeState, rowCount) == 0x44 ? 1 : -1];
typedef char GaugeTemplatesOffsetCheck[GAUGE_OFFSET(GaugeState, markerTemplates) == 0x144 ? 1 : -1];
typedef char GaugeOriginXOffsetCheck[GAUGE_OFFSET(SceneRecord, originX) == 2 ? 1 : -1];
typedef char GaugeOriginYOffsetCheck[GAUGE_OFFSET(SceneRecord, originY) == 4 ? 1 : -1];
typedef char GaugeStyleOffsetCheck[GAUGE_OFFSET(HudGaugeTable, markerStyle) == 0 ? 1 : -1];
typedef char GaugeTableSizeCheck[sizeof(HudGaugeTable) == 40 ? 1 : -1];
#undef GAUGE_OFFSET

extern GaugeState *data_ov001_020a04cc;
extern SceneTagTracker *GetSceneTagTracker(void);
extern SceneRecord *FindActiveRecordById(SceneTagTracker *tracker, u32 id);
extern SceneRecord *CopyElementLayout(SceneTagTracker *tracker, SceneRecord *record, const SceneRecord *layout);
extern SceneRecord *AddRecordFromTemplate(SceneTagTracker *tracker, const SceneRecord *layout, u16 id, int userData);
extern void func_ov027_020b8208(SceneTagTracker *tracker, SceneRecord *record, s16 x, s16 y);
extern void func_ov027_020b8230(SceneTagTracker *tracker, SceneRecord *record);

/* Two gauge rows share a marker; retain the first row's style until it is complete. */
void UpdateGaugeMarker(int row, BOOL filled, BOOL last)
{
    int *style = &gHudGaugeTable.markerStyle;
    GaugeState *state = data_ov001_020a04cc;
    int odd = row % 2;
    SceneTagTracker *tracker = GetSceneTagTracker();
    int half;
    u16 id;
    SceneRecord *record;

    if (odd == 1) {
        switch (*style) {
        case HUD_GAUGE_MARKER_FILLED_SINGLE:
            *style = filled ? HUD_GAUGE_MARKER_FILLED_PAIR : HUD_GAUGE_MARKER_PARTIAL_PAIR;
            break;
        case HUD_GAUGE_MARKER_EMPTY_SINGLE:
            *style = HUD_GAUGE_MARKER_EMPTY_PAIR;
            break;
        }
    } else {
        *style = filled ? HUD_GAUGE_MARKER_FILLED_SINGLE : HUD_GAUGE_MARKER_EMPTY_SINGLE;
    }

    if (last || odd == 1) {
        half = row / 2;
        id = (u16)(half + 50000);
        if (state->rowCount > 0 && half <= state->rowCount / 2) {
            record = FindActiveRecordById(tracker, id);
            CopyElementLayout(tracker, record, state->markerTemplates[*style]);
        } else {
            s16 x = state->markerTemplates[0]->originX;
            record = AddRecordFromTemplate(tracker, state->markerTemplates[*style], id, 11);
            func_ov027_020b8208(tracker, record, (s16)(x - half), state->markerTemplates[0]->originY);
        }
        func_ov027_020b8230(tracker, record);
        *style = HUD_GAUGE_MARKER_NONE;
    }
}
