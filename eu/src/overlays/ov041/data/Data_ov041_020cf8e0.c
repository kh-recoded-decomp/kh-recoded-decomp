#include "nitro/types.h"

extern void func_ov041_020bf0ec(void);
extern void func_ov041_020bf130(void);
extern void func_ov041_020bf180(void);
extern void StageStateFadeBgm(void);
extern void func_ov041_020bf234(void);
extern void func_ov041_020bf280(void);
extern void func_ov041_020bf924(void);
extern void func_ov041_020bfbe0(void);
extern void func_ov041_020bf39c(void);
extern void func_ov041_020bf474(void);
extern void func_ov041_020bf5b0(void);
extern void func_ov041_020bf82c(void);
extern void func_ov041_020bfe84(void);
extern void func_ov041_020bfff4(void);
extern void func_ov041_020c00a8(void);
extern void func_ov041_020c021c(void);
extern void StageStateNoop16(void);
extern void func_ov041_020c04a0(void);
extern void StageStateRunFieldOp428(void);
extern void func_ov041_020c0678(void);
extern void func_ov041_020c07b4(void);
extern void func_ov041_020c07ec(void);
extern void StageStateNoop22(void);

#pragma explicit_zero_data on

void (*gStageStateHandlers[23])(void) = {
    func_ov041_020bf0ec,
    func_ov041_020bf130,
    func_ov041_020bf180,
    StageStateFadeBgm,
    func_ov041_020bf234,
    func_ov041_020bf280,
    func_ov041_020bf924,
    func_ov041_020bfbe0,
    func_ov041_020bf39c,
    func_ov041_020bf474,
    func_ov041_020bf5b0,
    func_ov041_020bf82c,
    func_ov041_020bfe84,
    func_ov041_020bfff4,
    func_ov041_020c00a8,
    func_ov041_020c021c,
    StageStateNoop16,
    func_ov041_020c04a0,
    StageStateRunFieldOp428,
    func_ov041_020c0678,
    func_ov041_020c07b4,
    func_ov041_020c07ec,
    StageStateNoop22,
};
