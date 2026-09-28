#include "nitro/types.h"

typedef struct CardEvent {
    u32 flags;
    void *queueHead;
    void *queueTail;
} CardEvent;

typedef struct CardPollTask {
    CardEvent event;
    u8 alarm[0x28];
    BOOL (*poll)(u16 *lockId);
    u16 *arg;
    u32 unk_3c;
} CardPollTask;

extern void CARDi_LockResource_020091d4(s32 owner, u32 target);
extern void OS_InitEvent_02004d3c(CardEvent *event);
extern void OS_CreateAlarm_02004654(void *alarm);
extern BOOL IsResultZero_02009028(u16 *value);
extern void PollTaskAndReschedule_02008ff0(CardPollTask *task);
extern u32 OS_WaitEventEx_02004d50(CardEvent *event, u32 pattern, u32 mode, u32 clearBits);

void CARD_LockRom_02009150(u16 lockId)
{
    CardPollTask task;

    CARDi_LockResource_020091d4(lockId, 1);
    OS_InitEvent_02004d3c(&task.event);
    OS_CreateAlarm_02004654(task.alarm);
    task.poll = IsResultZero_02009028;
    task.arg = &lockId;
    PollTaskAndReschedule_02008ff0(&task);
    OS_WaitEventEx_02004d50(&task.event, 1, 0, 1);
}
