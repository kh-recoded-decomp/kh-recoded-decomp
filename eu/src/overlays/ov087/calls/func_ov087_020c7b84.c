#include "nitro/types.h"

extern u32 PlaySoundEffect();
extern u32 EnterSceneSlot();
extern u32 PlayFieldTrackSet();
extern u32 EnterSceneSlotAtSpawn();
extern u32 func_ov001_02064998();
extern void ClearResumeModePending(void);
extern u32 StartSubScene();
extern u32 GetActiveMenuScene();

void func_ov087_020c7b84(void) {
  int menu;
  u32 selection;

  menu = GetActiveMenuScene();
  selection = *(u32 *)(*(int *)(menu + 4) * 0x108 + menu + 0x118);
  if (*(int *)(menu + 0x10) == 0) {
    switch(*(u32 *)(menu + 0xbc0)) {
    case 0:
      func_ov001_02064998();
      break;
    case 1:
      EnterSceneSlot(selection,*(u32 *)(menu + 0xbc4));
      break;
    case 2:
      PlayFieldTrackSet();
      break;
    case 3:
      EnterSceneSlotAtSpawn(selection,*(u32 *)(menu + 0xbc4));
    }
    ClearResumeModePending();
    StartSubScene(0xffffffff,0xffffffff,1);
    PlaySoundEffect(0,1);
    return;
  }
}
