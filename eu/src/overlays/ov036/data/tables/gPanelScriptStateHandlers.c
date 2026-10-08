#include "nitro/types.h"

extern void func_ov036_020ba914(void);
extern void StartPanelSceneLoad(void);
extern void RunPanelScriptFrame(void); /* RunPanelScriptFrame */
extern void RunPanelSubScriptFrame(void); /* RunPanelSubScriptFrame */
extern void FinishPanelSceneSetup(void);
extern void ShutdownPanelScene_020bab74(void); /* ShutdownPanelScene */
extern void FinishPanelSceneTransition(void);
extern void ClearPanelSceneTransition(void);

void (*gPanelScriptStateHandlers[8])(void) = {
    func_ov036_020ba914,
    StartPanelSceneLoad,
    RunPanelScriptFrame, /* RunPanelScriptFrame */
    RunPanelSubScriptFrame, /* RunPanelSubScriptFrame */
    FinishPanelSceneSetup,
    ShutdownPanelScene_020bab74, /* ShutdownPanelScene */
    FinishPanelSceneTransition,
    ClearPanelSceneTransition,
};
