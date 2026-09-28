#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x28];
    u32 field28;
} SchedulerGlobals_02056b50;

extern SchedulerGlobals_02056b50 data_02056b50;
extern u32 func_02004938(void);
extern void func_0200494c(u32 state);

u32 SetSchedulerField28_02002d38(u32 value)
{
    u32 savedState = func_02004938();
    u32 oldValue = data_02056b50.field28;

    data_02056b50.field28 = value;
    func_0200494c(savedState);
    return oldValue;
}
