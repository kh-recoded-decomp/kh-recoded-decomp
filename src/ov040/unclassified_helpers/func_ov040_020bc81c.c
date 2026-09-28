#include "nitro/types.h"

extern void func_ov040_020bc5b8();
extern void func_ov040_020bc650();
extern void func_ov040_020bc710();
extern void func_ov040_020bc784();

void func_ov040_020bc81c(u32 handle)
{
    func_ov040_020bc5b8();
    func_ov040_020bc650(handle);
    func_ov040_020bc784(handle);
    func_ov040_020bc710(handle);
}
