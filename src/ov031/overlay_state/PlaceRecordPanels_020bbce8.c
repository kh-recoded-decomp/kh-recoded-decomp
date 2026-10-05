#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 position;
    s32 param;
    s32 itemId;
} PanelSpawn;

typedef struct {
    u8 pad_00[0x8];
    VecFx32 origin;
    u8 pad_14[0x20];
    PanelSpawn *panelSpawns;
    u8 pad_38[0x3];
    u8 panelCount;
} ActiveRecord;

typedef struct {
    u8 pad_00[0x44];
    s32 recordIndex;
    u8 pad_48[0x8];
    ActiveRecord *records;
} OverlayState;

typedef struct {
    u8 pad_00[0x7d];
    u8 type;
} PanelInfo;

typedef struct {
    u8 pad_00[0x8];
    PanelInfo *info;
    u8 pad_0c[0x42];
    u16 flags;
} Panel;

typedef struct {
    u8 pad_00[0x46];
    u16 panelCount;
} PanelLayer;

extern OverlayState *g_activeState_020bc800;
extern void *func_ov001_0208723c(void);
extern int func_ov001_0207f018(void);
extern PanelLayer *func_ov001_0207f028(int index);
extern Panel *func_ov001_0207f038(int layer, int index);
extern BOOL func_ov001_02082708(Panel *panel);
extern s8 GetCtxModeByte_02068084(void);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void InitItemPanel_02085ea4(Panel *panel, const VecFx32 *position, int itemId, int param);

static inline u8 GetPanelType(int layerIndex, int panelIndex)
{
    return func_ov001_0207f038(layerIndex, panelIndex)->info->type;
}

void PlaceRecordPanels_020bbce8(void)
{
    ActiveRecord *record;
    u32 placed;
    int layerCount;
    int i;
    int j;
    PanelLayer *layer;
    int count;
    Panel *panel;
    VecFx32 position;

    record = &g_activeState_020bc800->records[g_activeState_020bc800->recordIndex];
    if (record->panelCount == 0 || func_ov001_0208723c() == NULL) {
        return;
    }
    placed = 0;
    layerCount = func_ov001_0207f018();
    for (i = 0; i < layerCount; i++) {
        j = 0;
        layer = func_ov001_0207f028(i);
        if (layer != NULL && layer->panelCount != 0 && GetPanelType(i, j) == 11) {
            count = layer->panelCount;
            for (; j < count; j++) {
                panel = func_ov001_0207f038(i, j);
                if ((panel->flags & 4) && !func_ov001_02082708(panel)) {
                    position = record->panelSpawns[placed].position;
                    if (GetCtxModeByte_02068084() != 6) {
                        ScaleVecFx32InPlace_0204a5e4(&position, 0xaab);
                    }
                    VEC_Subtract_01ff9e3c(&position, &record->origin, &position);
                    InitItemPanel_02085ea4(panel, &position, record->panelSpawns[placed].itemId,
                                           record->panelSpawns[placed].param);
                    placed++;
                    if (placed == record->panelCount) {
                        return;
                    }
                }
            }
            break;
        }
    }
}


