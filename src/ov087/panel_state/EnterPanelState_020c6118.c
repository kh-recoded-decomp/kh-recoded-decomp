#include "nitro/types.h"

typedef void (*StateEnterFunc)(void *scene, int previousState);

typedef struct {
    StateEnterFunc handlers[18];
} StateHandlerTable;

extern const StateHandlerTable data_ov087_020c7dc4;
extern void *func_ov039_020bc1bc(void);
extern void *func_ov027_020b90a4(void *container, int elementId);
extern void func_ov027_020b9580(void *container, void *element, BOOL visible);
extern void InvokeSlotHandlers_020c46e0(void *scene);
extern void func_ov087_020c4a48(void *scene);

void EnterPanelState_020c6118(void *scene, int stateId, int previousState)
{
    void *container = func_ov039_020bc1bc();
    StateHandlerTable table = data_ov087_020c7dc4;
    StateEnterFunc handler;

    func_ov027_020b9580(container, func_ov027_020b90a4(container, 0xc), FALSE);
    handler = table.handlers[stateId];
    if (handler == NULL) {
        return;
    }
    InvokeSlotHandlers_020c46e0(scene);
    func_ov087_020c4a48(scene);
    handler(scene, previousState);
}
