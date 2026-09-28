#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    u32 rescheduleCount;
} ThreadInfo_02056b50;

extern ThreadInfo_02056b50 data_02056b50;
extern int func_02004938(void);
extern void func_0200494c(int state);

u32 DisableScheduler_02002d70(void)
{
    int state = func_02004938();
    u32 count;

    if (data_02056b50.rescheduleCount < (u32)(0 - 1)) {
        count = data_02056b50.rescheduleCount++;
    }
    func_0200494c(state);

    return count;
}
