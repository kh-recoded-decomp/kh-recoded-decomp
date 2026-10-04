#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0xc];
    int id;
} Widget;

typedef struct {
    int stateId;
    void *focusElement;
} PanelStackEntry;

typedef struct {
    u8 pad_000[0xb70];
    PanelStackEntry stack[6];
    int depth;
    int unk_ba4;
    BOOL hasAvailableItem;
    u8 pad_bac[8];
    int lastWidgetId;
} PanelScene;

extern void *func_ov039_020bc1bc(void);
extern void func_ov027_020b9360(void *panel, Widget *widget, fx32 *position, int mode);
extern void *func_ov027_020b90a4(void *panel, int elementId);
extern void func_ov027_020b91c8(void *panel, void *element, const fx32 *position, int mode);
extern void SetInfoWindowVisible_020c431c(PanelScene *scene, BOOL visible);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void MoveCursorToWidget_020c43c4(PanelScene *scene, Widget *widget, BOOL narrow, BOOL playSound)
{
    void *panel = func_ov039_020bc1bc();
    fx32 position[2];
    fx32 offset;

    func_ov027_020b9360(panel, widget, position, 0);
    offset = 0x30000;
    if (narrow == FALSE) {
        offset = 0x40000;
    }
    position[0] -= offset;
    func_ov027_020b91c8(panel, func_ov027_020b90a4(panel, 0), position, 0);
    switch (scene->stack[scene->depth].stateId) {
    case 1:
    case 2:
    case 3:
        if (widget->id == 2) {
            SetInfoWindowVisible_020c431c(scene, scene->hasAvailableItem);
        } else {
            SetInfoWindowVisible_020c431c(scene, FALSE);
        }
        break;
    }
    if (playSound && scene->lastWidgetId != widget->id) {
        PlaySoundEffect_0204d924(0, 0);
    }
    scene->lastWidgetId = widget->id;
}
