#include "nitro/types.h"

extern void BeginResumeMode(void); /* BeginResumeMode */
extern void func_ov033_020ba71c(void);
extern void func_ov033_020ba74c(void);
extern void func_ov033_020ba7f0(void);

void (*gResumeModeHandlers[4])(void) = {
    BeginResumeMode,
    func_ov033_020ba71c,
    func_ov033_020ba74c,
    func_ov033_020ba7f0,
};
