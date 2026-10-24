#include "eu/libs/nitro/os/os_interrupt_state.h"

#define CancelAlarm OS_CancelAlarm
#define SetAlarmTimer OSi_SetTimer
#define alarmQueue OSi_AlarmState
#include "src/arm9/nitro_os/CancelAlarm_020043a8.c"
