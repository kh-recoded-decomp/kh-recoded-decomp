#include "nitro/types.h"

extern void RequestEntryTransitionIfIdle_020c1764(void);
extern void func_ov091_020c1760(void);
extern void func_ov091_020c1790(void);

void (*const data_ov091_020c281c[3])(void) = {
    func_ov091_020c1760,
    RequestEntryTransitionIfIdle_020c1764,
    func_ov091_020c1790,
};
