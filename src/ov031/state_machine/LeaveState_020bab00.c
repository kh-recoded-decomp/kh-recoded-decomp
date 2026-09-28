#include "nitro/types.h"

extern void func_02035dd0(void);
extern void func_ov001_02067d48(void);
extern void func_ov001_0206daa8(void);
extern void func_ov001_020876ac(void);
extern void func_ov021_020af508(u32 a);
extern void func_ov031_020bb2d4(void);

void LeaveState_020bab00(void)
{
    func_ov021_020af508(1);
    func_ov001_02067d48();
    func_ov031_020bb2d4();
    func_ov001_0206daa8();
    func_02035dd0();
    func_ov001_020876ac();
}
