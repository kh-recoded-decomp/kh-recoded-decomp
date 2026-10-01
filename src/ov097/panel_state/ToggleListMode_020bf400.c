#include "nitro/types.h"

typedef struct {
    s32 selectedEntry;
    s32 listMode;
} MenuScene;

extern void SetPanelSlotFlag_020bff94(int listIndex, int slotIndex, BOOL enabled, MenuScene *scene);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void ToggleListMode_020bf400(MenuScene *scene)
{
    scene->listMode = (scene->listMode + 1) % 2;
    SetPanelSlotFlag_020bff94(0, 0, scene->listMode != 1, scene);
    PlaySoundEffect_0204d924(0, 1);
}
