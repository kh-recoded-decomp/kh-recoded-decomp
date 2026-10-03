#include "nitro/types.h"

extern void func_ov000_02063044(void);
extern void func_ov000_02063070(void);
extern void func_ov000_02063108(void);
extern void func_ov000_02063170(void);
extern void func_ov000_020631d8(void);

void (*data_ov000_02063850[4])(void) = {
    func_ov000_02063108,
    func_ov000_02063170,
    func_ov000_020631d8,
    NULL,
};

void (*data_ov000_02063848[2])(void) = {
    func_ov000_02063044,
    func_ov000_02063070,
};
