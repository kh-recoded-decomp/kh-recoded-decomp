#include "src/overlays/ov001/SceneTaskTables.h"

/* The legacy linker name belongs to the task-release routine. */
#define ReleaseSceneTask PXI_Init_0202a64c
extern void ReleaseSceneTask(u32 handle);
extern BOOL IsSubScene9TaskActive(void);

void DestroySubScene9Task(void)
{
    BOOL active;

    active = IsSubScene9TaskActive();
    if (active != 0) {
        ReleaseSceneTask(gSubScene9TaskHandle);
        gSubScene9TaskHandle = 0xffffffff;
    }
}
