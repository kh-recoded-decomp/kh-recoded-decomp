#include "nitro/types.h"

#define SND_ALARM_NUM 8

typedef void (*SNDAlarmHandler)(void *arg);

typedef struct AlarmCallbackInfo {
    SNDAlarmHandler func;
    void *arg;
    u8 id;
    u8 pad_09[3];
} AlarmCallbackInfo;

extern AlarmCallbackInfo data_02059720[SND_ALARM_NUM];

void SND_AlarmInit_0200f4d0(void)
{
    int alarmNo;

    for (alarmNo = 0; alarmNo < SND_ALARM_NUM; alarmNo++) {
        data_02059720[alarmNo].func = NULL;
        data_02059720[alarmNo].arg = NULL;
        data_02059720[alarmNo].id = 0;
    }
}
