#include "nitro/types.h"

typedef int (*SceneStateFunc)(void);

typedef struct {
    u32 id;
    void (*init)(void);
    void (*close)(void);
    u32 workSize;
    u32 flags;
} OverlayDesc;

extern void InitMovieOverlayState_020ba3e0(void);
extern void MoviePlayer_Close_020ba518(void);
extern int func_ov030_020ba568(void);
extern int FinishSceneSetup_020ba594(void);
extern int func_ov030_020ba5c8(void);
extern int func_ov030_020ba5f4(void);
extern int func_ov030_020ba60c(void);
extern int MoviePlayer_EnterPlayback_020ba678(void);
extern int func_ov030_020ba754(void);
extern int func_ov030_020ba788(void);
extern int func_ov030_020ba824(void);
extern int func_ov030_020ba854(void);
extern int SceneState_WaitScreenIdle_020ba874(void);
extern int EnterState12WithHalfRate_020ba8d0(void);
extern int func_ov030_020ba8ec(void);
extern int func_ov030_020ba910(void);
extern int func_ov030_020ba944(void);
extern int func_ov030_020ba96c(void);
extern int func_ov030_020ba9a8(void);
extern int MoviePlayer_Stop_020ba9d0(void);
extern int func_ov030_020baa7c(void);

s32 data_ov030_020bcf80 = -1;

OverlayDesc data_ov030_020bcf84 = {
    0x2000e, InitMovieOverlayState_020ba3e0, MoviePlayer_Close_020ba518, 0x68, 0,
};

SceneStateFunc data_ov030_020bcf98[] = {
    func_ov030_020ba568,
    FinishSceneSetup_020ba594,
    func_ov030_020ba5c8,
    func_ov030_020ba5f4,
    func_ov030_020ba60c,
    MoviePlayer_EnterPlayback_020ba678,
    func_ov030_020ba754,
    func_ov030_020ba788,
    func_ov030_020ba824,
    func_ov030_020ba854,
    SceneState_WaitScreenIdle_020ba874,
    EnterState12WithHalfRate_020ba8d0,
    func_ov030_020ba8ec,
    func_ov030_020ba910,
    func_ov030_020ba944,
    func_ov030_020ba96c,
    func_ov030_020ba9a8,
    MoviePlayer_Stop_020ba9d0,
    func_ov030_020baa7c,
};
