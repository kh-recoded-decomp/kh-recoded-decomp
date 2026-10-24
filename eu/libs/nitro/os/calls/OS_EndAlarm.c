#include "eu/libs/nitro/os/os_interrupt_state.h"

#define EndAlarmSystem OS_EndAlarm
#define ReleaseAlarmTimer OSi_UnsetTimerReserved
#define alarmQueue OSi_AlarmState
#include "src/arm9/nitro_os/EndAlarmSystem_020041b8.c"
