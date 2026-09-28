#include "nitro/types.h"

extern void *func_ov039_020bc1bc(void);
extern int func_ov087_020c4758(void *scene, int headerMessageId, int footerMessageId);
extern void func_ov087_020c4c70(void *scene);
extern void *func_ov027_020b90a4(void *container, int elementId);
extern void func_ov027_020b9580(void *container, void *element, BOOL visible);

void OpenPromptMessage0E_020c5c44(void *scene)
{
    void *container = func_ov039_020bc1bc();
    int frameId = func_ov087_020c4758(scene, 0x0e, 0x15);
    void *frame;

    func_ov087_020c4c70(scene);
    frame = func_ov027_020b90a4(container, frameId);
    func_ov027_020b9580(container, frame, TRUE);
}
