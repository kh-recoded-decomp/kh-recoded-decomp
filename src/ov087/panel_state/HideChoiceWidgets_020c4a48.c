#include "nitro/types.h"

typedef struct {
    int values[3];
} IdTriple;

typedef struct {
    int values[2];
} IdPair;

extern const IdTriple data_ov087_020c7ca0;
extern const IdPair data_ov087_020c7c78;
extern void *func_ov039_020bc1bc(void);
extern void CallStateWidget_020bc14c(int layerId, int x, int y, int width, int height);
extern void *FindWidgetById_020b90a4(void *container, int elementId);
extern void SetEntrySlotsVisible_020b9580(void *container, void *element, BOOL visible);

void HideChoiceWidgets_020c4a48(void)
{
    IdTriple choiceIds = data_ov087_020c7ca0;
    IdPair arrowIds = data_ov087_020c7c78;
    void *container = func_ov039_020bc1bc();
    int i;

    CallStateWidget_020bc14c(10, 0, 0xc, 0x20, 0xc);
    for (i = 0; i < 3; i++) {
        SetEntrySlotsVisible_020b9580(container, FindWidgetById_020b90a4(container, choiceIds.values[i]), FALSE);
    }
    for (i = 0; i < 2; i++) {
        SetEntrySlotsVisible_020b9580(container, FindWidgetById_020b90a4(container, arrowIds.values[i]), FALSE);
    }
    SetEntrySlotsVisible_020b9580(container, FindWidgetById_020b90a4(container, 5), FALSE);
    SetEntrySlotsVisible_020b9580(container, FindWidgetById_020b90a4(container, 6), FALSE);
    SetEntrySlotsVisible_020b9580(container, FindWidgetById_020b90a4(container, 0xe), FALSE);
    SetEntrySlotsVisible_020b9580(container, FindWidgetById_020b90a4(container, 0xb), FALSE);
}
