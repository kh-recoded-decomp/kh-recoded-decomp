#include "nitro/types.h"

extern void func_ov078_020c4748(void);
extern void func_ov078_020c4774(void *entity);
extern void func_ov078_020c48dc(void *entity);
extern void func_ov078_020c4980(void *entity);
extern void func_ov078_020c4b18(void *entity);

/* Runs a fixed init sequence on an entity */
void InitSequence_020c471c(void *entity)
{
    func_ov078_020c4748();
    func_ov078_020c4980(entity);
    *(u32 *)((u8 *)entity + 0x5d4) = 0;
    func_ov078_020c4774(entity);
    func_ov078_020c48dc(entity);
    func_ov078_020c4b18(entity);
}
