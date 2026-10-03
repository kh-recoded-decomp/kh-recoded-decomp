#include "nitro/types.h"
#include "nitro/rtc.h"

typedef struct ContextConfig {
    u8 pad_0000[0x1ac8];
    u32 unk_1ac8_b0 : 27;
    u32 day : 5;
    u32 second : 6;
    u32 progress : 7;
    u32 year : 7;
    u32 minute : 6;
    u32 hour : 6;
    u32 month : 4;
    u32 unk_1ad0_b4 : 28;
} ContextConfig;

extern ContextConfig *func_ov002_02066fe0(void);
extern int RTCi_RunAsyncCommandExAndWait_0200e594(RTCDate *date, RTCTime *time);

void StampContextDateTime_02067564(int progress)
{
    RTCDate date;
    RTCTime time;
    ContextConfig *config = func_ov002_02066fe0();

    if (progress > 100) {
        progress = 100;
    }
    config->progress = progress;
    RTCi_RunAsyncCommandExAndWait_0200e594(&date, &time);
    config->year = date.year;
    config->month = date.month;
    config->day = date.day;
    config->hour = time.hour;
    config->minute = time.minute;
    config->second = time.second;
}
