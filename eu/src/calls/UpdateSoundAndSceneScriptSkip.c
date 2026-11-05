#include "nitro/types.h"

extern void SoundMgr_Update(void);
extern int AdvanceCurrentSceneScriptSkip(void);
extern void ResetPanelFieldB8AndNotify(void);

void UpdateSoundAndSceneScriptSkip(void) {
    SoundMgr_Update();
    if (AdvanceCurrentSceneScriptSkip() != 0) {
        ResetPanelFieldB8AndNotify();
    }
}
