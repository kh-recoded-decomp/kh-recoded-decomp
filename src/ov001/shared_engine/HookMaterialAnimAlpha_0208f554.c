#include "nitro/types.h"

typedef void (*AnmFunc)(void *result, const void *anmObj, u32 dataIdx);

typedef struct AnmObj {
    u32 frame;
    u32 ratio;
    void *resAnm;
    AnmFunc funcAnm;
    struct AnmObj *next;
} AnmObj;

typedef struct AnimTarget {
    u8 pad_00[4];
    s16 slotCount;
    u8 pad_06[0x12];
    AnmObj **slots;
} AnimTarget;

extern void CalcNsBmaAnimation_0201c508(void *result, const void *anmObj, u32 dataIdx);
extern void CalcMaterialAnimWithGlobalAlpha_0208f4ac(void *result, const void *anmObj, u32 dataIdx);

void HookMaterialAnimAlpha_0208f554(AnimTarget *target)
{
    int i;
    AnmObj *anm;

    if (target->slotCount != 0 && target->slots != NULL) {
        for (i = 0; i < target->slotCount; i++) {
            for (anm = target->slots[i]; anm != NULL; anm = anm->next) {
                if (anm->funcAnm == CalcNsBmaAnimation_0201c508) {
                    anm->funcAnm = CalcMaterialAnimWithGlobalAlpha_0208f4ac;
                }
            }
        }
    }
}
