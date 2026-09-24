/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern void OSi_SetTimerReserved(int);
extern void OS_DisableIrqMask(unsigned int);

typedef struct {
    unsigned short active;
    char padding[2];
    void *head;
    void *tail;
} AlarmSchedulerState;

extern AlarmSchedulerState alarmScheduler;

void InitializeAlarmSystem_0200417c(void)
{
    if (alarmScheduler.active != 0)
        return;

    alarmScheduler.active = 1;
    OSi_SetTimerReserved(1);
    alarmScheduler.head = 0;
    alarmScheduler.tail = 0;
    OS_DisableIrqMask(0x10);
}
