#include "nitro/types.h"

typedef struct {
    s8 ids[5];
} EntrySceneTable;

typedef struct {
    int cursorRow;
} MenuScene;

extern EntrySceneTable data_ov091_020c2814;
extern BOOL func_ov091_020c1754(void);
extern void PushStackEntry_020bc874(int value);
extern void func_ov039_020bbf78(int scene, int arg, int mode);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void OpenSelectedEntryScene_020beee0(MenuScene *scene)
{
    EntrySceneTable scenes;

    if (func_ov091_020c1754()) {
        return;
    }
    scenes = data_ov091_020c2814;
    PushStackEntry_020bc874(scene->cursorRow);
    func_ov039_020bbf78(scenes.ids[scene->cursorRow], -1, 1);
    PlaySoundEffect_0204d924(0, 1);
}
