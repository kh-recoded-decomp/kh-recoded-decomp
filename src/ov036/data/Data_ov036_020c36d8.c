#include "nitro/types.h"

extern void RunPanelScriptFrame_020ba970(void);
extern void RunPanelSubScriptFrame_020ba9d0(void);
extern void ShutdownPanelScene_020bab54(void);
extern void func_ov036_020ba8f4(void);
extern void func_ov036_020ba928(void);
extern void func_ov036_020baa38(void);
extern void func_ov036_020bacd0(void);
extern void func_ov036_020bad14(void);

void (*data_ov036_020c36d8[8])(void) = {
    func_ov036_020ba8f4,
    func_ov036_020ba928,
    RunPanelScriptFrame_020ba970,
    RunPanelSubScriptFrame_020ba9d0,
    func_ov036_020baa38,
    ShutdownPanelScene_020bab54,
    func_ov036_020bacd0,
    func_ov036_020bad14,
};
