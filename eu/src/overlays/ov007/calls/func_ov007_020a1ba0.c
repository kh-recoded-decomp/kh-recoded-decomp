#include "nitro/types.h"

extern int func_ov001_02067ed4(void);
extern int func_ov035_020bae94(void);
extern int UpdateEventTriggerDelay(void *obj);

typedef struct {
    void *callback;
    u8 pad_04[0x0C];
    s8 result;
    u8 pad_11;
    s8 expectedValue;
    u8 pad_13;
    s8 alreadyRun;
} UnkState_020a1b80;

int func_ov007_020a1ba0(UnkState_020a1b80 *obj)
{
    int value;

    obj->result = 0;
    value = func_ov001_02067ed4();
    if (obj->expectedValue != value) {
        return 0;
    }
    if (obj->alreadyRun == 0 && (value = func_ov035_020bae94(), value != 0)) {
        obj->result = 1;
    }
    value = UpdateEventTriggerDelay(obj);
    if (value != 0) {
        return obj->result;
    }
    return 0;
}
