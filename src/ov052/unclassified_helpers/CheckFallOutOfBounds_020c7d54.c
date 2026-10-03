#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*StateCallback)(int entity, int state);

extern VecFx32 *func_ov052_020ceb54(int entity);
extern s32 func_ov001_02063a38(void);
extern BOOL func_ov001_020645c8(u32 value);
extern BOOL CheckCarriedActorEscape_020bbf78(int entity);
extern void Obj_SetPosition_0203569c(void *object, const VecFx32 *position);

void CheckFallOutOfBounds_020c7d54(int entity)
{
    VecFx32 *position = func_ov052_020ceb54(entity);
    VecFx32 target;
    if (func_ov001_02063a38() == 4) {
        CheckCarriedActorEscape_020bbf78(entity);
        return;
    }
    if (!func_ov001_020645c8(0x3632) && func_ov052_020ceb54(entity)->y <= -0x3000) {
        target = *position;
        target.y = 0x14000;
        Obj_SetPosition_0203569c(*(void **)(entity + 0x230), &target);
        (*(StateCallback *)(entity + 0x10ec))(entity, 4);
    }
}
