#include "nitro/types.h"

extern void MoveCursorToSelectedColumn_020cc8f0(void);
extern void _fp_init_020cc8e8(void);
extern void _fp_init_020cc8ec(void);
extern void _fp_init_020cc914(void);
extern void func_ov075_020cc918(void);

void (*const data_ov075_020d1408[5])(void) = {
    _fp_init_020cc8e8,
    _fp_init_020cc914,
    func_ov075_020cc918,
    MoveCursorToSelectedColumn_020cc8f0,
    _fp_init_020cc8ec,
};
