#include "libs/nitro/rtc/rtc_internal.h"

void RtcWaitBusy(void)
{
    while (RTCi_Lock == RTC_LOCK_ON) {
    }
}
