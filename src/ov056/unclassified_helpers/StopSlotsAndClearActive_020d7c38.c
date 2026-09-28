#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x194];
    BOOL isActive;
} BeamEntity;

extern void func_ov021_020aeb6c(BeamEntity *entity);

void StopSlotsAndClearActive_020d7c38(BeamEntity *entity)
{
    func_ov021_020aeb6c(entity);
    entity->isActive = FALSE;
}
