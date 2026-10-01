#include "nitro/types.h"

typedef struct {
    int stateId;
    void *focusElement;
} PanelStackEntry;

typedef struct {
    u8 pad_000[0xb70];
    PanelStackEntry stack[6];
    int depth;
} PanelScene;

extern void *func_ov039_020bc1bc(void);
extern void *func_ov027_020b90f4(void *container);
extern void func_ov087_020c6118(PanelScene *scene, int newState, int oldState);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void PushPanelState_020c61b0(PanelScene *scene, int stateId)
{
    int previousState = scene->stack[scene->depth].stateId;

    scene->depth++;
    scene->stack[scene->depth].stateId = stateId;
    scene->stack[scene->depth].focusElement = func_ov027_020b90f4(func_ov039_020bc1bc());
    func_ov087_020c6118(scene, stateId, previousState);
    if (stateId != 0x10 && stateId != 0x11) {
        PlaySoundEffect_0204d924(0, 1);
    }
}
