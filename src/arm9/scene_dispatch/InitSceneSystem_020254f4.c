#include "nitro/types.h"

typedef int (*SceneStepFn)(void);

extern void func_0202c20c(void);
extern void func_0204d4ac(int a, int b);
extern void func_0204d5f0(int a);
extern void ResetSceneCtl_02025550(void);
extern void func_02028bcc(void);
extern void SetPendingScene_02025644(s32 pendId, s32 pendArg);
extern int func_02025540(void);
extern u32 g_engineState_02fffc20;

SceneStepFn InitSceneSystem_020254f4(void)
{
    func_0202c20c();
    func_0204d4ac(0, 0);
    func_0204d5f0(0);
    ResetSceneCtl_02025550();
    func_02028bcc();
    SetPendingScene_02025644(1, g_engineState_02fffc20);
    return func_02025540;
}
