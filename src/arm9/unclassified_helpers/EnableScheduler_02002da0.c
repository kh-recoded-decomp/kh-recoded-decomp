#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    u32 rescheduleCount;
} SchedulerGlobals_02056b50;

extern SchedulerGlobals_02056b50 data_02056b50;
extern u32 func_02004938(void);
extern void func_0200494c(u32 state);

u32 EnableScheduler_02002da0(void)
{
    u32 savedState = func_02004938();
    u32 count = 0;

    if (data_02056b50.rescheduleCount != 0) {
        count = data_02056b50.rescheduleCount;
        data_02056b50.rescheduleCount = count - 1;
    }
    func_0200494c(savedState);
    return count;
}
