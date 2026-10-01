#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroupObject {
    u8 pad_00[0x76];
    s8 displayScale;
    u8 pad_77[0xBF - 0x77];
    s8 scaleLevel;
} GroupObject;

typedef struct ObjectGroup {
    u8 pad_00[0x1C];
    fx32 scaleX;
    fx32 scaleY;
} ObjectGroup;

extern ObjectGroup *func_ov032_020bbc60(void *object);
extern int ArmObject_0205116c(void);
extern fx32 FixedPointMultiply12_02006450(fx32 left, fx32 right);
extern int func_ov032_020bd23c(fx32 value);

void ApplyGroupScale_020bd248(GroupObject *object) {
    ObjectGroup *group = func_ov032_020bbc60(object);
    fx32 scale = FixedPointMultiply12_02006450(0x1000, ArmObject_0205116c());
    scale = FixedPointMultiply12_02006450(group->scaleX, scale);
    if (scale <= 0x1000) {
        scale = 0x1000;
    }
    group->scaleX = scale;
    group->scaleY = scale;
    object->scaleLevel = func_ov032_020bd23c(scale);
    object->displayScale = object->scaleLevel;
}
