#include "nitro/types.h"

extern int *SelectSubObject_020aa144(void *owner, int which);

int GetSubObjectValue_020aa598(void *owner, int which, int index)
{
    int result = 0x7fffffff;
    int value = SelectSubObject_020aa144(owner, which)[index];
    if (value != -0x1000) {
        result = value;
    }
    return result;
}
