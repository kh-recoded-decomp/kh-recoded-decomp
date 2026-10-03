#include "nitro/types.h"

extern void BeginResumeMode_020ba5e4(void);
extern void func_ov033_020ba6fc(void);
extern void func_ov033_020ba72c(void);
extern void func_ov033_020ba7d0(void);

void (*data_ov033_020baa84[4])(void) = {
    BeginResumeMode_020ba5e4,
    func_ov033_020ba6fc,
    func_ov033_020ba72c,
    func_ov033_020ba7d0,
};
