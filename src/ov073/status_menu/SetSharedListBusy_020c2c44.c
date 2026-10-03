#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;

typedef struct MenuSharedState {
    s8 selectedIndex;
    u8 pad_0001[0xb44 - 1];
    u8 list[0x10e0 - 0xb44];
    ResourceContainer *container;
} MenuSharedState;

extern MenuSharedState *func_ov039_020bc630(void);
extern BOOL func_ov039_020bc0d4(void);
extern void SetListWidgetBusy_020c4044(void *list, BOOL busy);
extern void *FindWidgetById_020b90a4(ResourceContainer *container, int id);
extern void func_ov027_020b9580(ResourceContainer *container, void *element, BOOL visible);

void SetSharedListBusy_020c2c44(BOOL busy)
{
    MenuSharedState *state = func_ov039_020bc630();
    void *list = state->list;
    BOOL visible;

    if (state->selectedIndex == 4) {
        SetListWidgetBusy_020c4044(list, busy);
        if (busy == 0 && func_ov039_020bc0d4() == 0) {
            visible = TRUE;
        } else {
            visible = FALSE;
        }
        func_ov027_020b9580(state->container, FindWidgetById_020b90a4(state->container, 0xe), visible);
    }
}
