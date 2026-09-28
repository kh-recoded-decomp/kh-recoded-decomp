#include "nitro/types.h"
#include "nitro/rtc.h"

typedef int PXIFifoTag;

typedef struct RtcState {
    u16 initialized;
    u8 pad_02[2];
    RTCWork work;
} RtcState;

extern RtcState data_02057c0c;
#define rtcWork data_02057c0c.work
#define rtcRawData ((RTCRawData *)0x02fffde8)

extern u32 RtcBCD2HEX_0200e878(u32 bcd);
extern RTCWeek RTC_GetDayOfWeek_0200e934(RTCDate *date);
extern BOOL RTCi_WriteRawStatus2Async_0200e908(void);

void RtcCommonCallback_0200e5b8(PXIFifoTag tag, u32 data, BOOL err)
{
    RTCResult result;
    RTCPxiResult pxiresult;
    u8 command;
    RTCCallback callback;

    if (err) {
        if (rtcWork.index) {
            rtcWork.index = 0;
        }

        if (rtcWork.lock != RTC_LOCK_OFF) {
            rtcWork.lock = RTC_LOCK_OFF;
        }

        if (rtcWork.callback) {
            callback = rtcWork.callback;
            rtcWork.callback = NULL;
            callback(RTC_RESULT_FATAL_ERROR, rtcWork.callbackArg);
        }

        return;
    }

    command = (u8)((data & RTC_PXI_COMMAND_MASK) >> RTC_PXI_COMMAND_SHIFT);
    pxiresult = (RTCPxiResult)((data & RTC_PXI_RESULT_MASK) >> RTC_PXI_RESULT_SHIFT);

    if (command == RTC_PXI_COMMAND_INTERRUPT) {
        if (rtcWork.interrupt) {
            rtcWork.interrupt();
        }
        return;
    }

    if (pxiresult == RTC_PXI_RESULT_SUCCESS) {
        result = RTC_RESULT_SUCCESS;
        switch (rtcWork.sequence) {
        case RTC_SEQ_GET_DATE:
        {
            RTCDate *dst = (RTCDate *)(rtcWork.buffer[0]);
            RTCRawDate *src = &(rtcRawData->t.date);

            dst->year = RtcBCD2HEX_0200e878(src->year);
            dst->month = RtcBCD2HEX_0200e878(src->month);
            dst->day = RtcBCD2HEX_0200e878(src->day);
            dst->week = RTC_GetDayOfWeek_0200e934(dst);
        }
        break;
        case RTC_SEQ_GET_TIME:
        {
            RTCTime *dst = (RTCTime *)(rtcWork.buffer[0]);
            RTCRawTime *src = &(rtcRawData->t.time);

            dst->hour = RtcBCD2HEX_0200e878(src->hour);
            dst->minute = RtcBCD2HEX_0200e878(src->minute);
            dst->second = RtcBCD2HEX_0200e878(src->second);
        }
        break;
        case RTC_SEQ_GET_DATETIME:
        {
            RTCDate *dst = (RTCDate *)(rtcWork.buffer[0]);
            RTCRawDate *src = &(rtcRawData->t.date);

            dst->year = RtcBCD2HEX_0200e878(*(u32 *)src & 0x000000ff);
            dst->month = RtcBCD2HEX_0200e878(src->month);
            dst->day = RtcBCD2HEX_0200e878(src->day);
            dst->week = RTC_GetDayOfWeek_0200e934(dst);
        }
        {
            RTCTime *dst = (RTCTime *)(rtcWork.buffer[1]);
            RTCRawTime *src = &(rtcRawData->t.time);

            dst->hour = RtcBCD2HEX_0200e878(src->hour);
            dst->minute = RtcBCD2HEX_0200e878(src->minute);
            dst->second = RtcBCD2HEX_0200e878(src->second);
        }
        break;
        case RTC_SEQ_SET_DATE:
        case RTC_SEQ_SET_TIME:
        case RTC_SEQ_SET_DATETIME:
            break;
        case RTC_SEQ_GET_ALARM1_STATUS:
        {
            RTCAlarmStatus *dst = (RTCAlarmStatus *)(rtcWork.buffer[0]);
            RTCRawStatus2 *src = &(rtcRawData->a.status2);

            switch (src->intr_mode) {
            case RTC_INTERRUPT_MODE_ALARM:
                *dst = RTC_ALARM_STATUS_ON;
                break;
            default:
                *dst = RTC_ALARM_STATUS_OFF;
            }
        }
        break;
        case RTC_SEQ_GET_ALARM2_STATUS:
        {
            RTCAlarmStatus *dst = (RTCAlarmStatus *)(rtcWork.buffer[0]);
            RTCRawStatus2 *src = &(rtcRawData->a.status2);

            if (src->intr2_mode) {
                *dst = RTC_ALARM_STATUS_ON;
            } else {
                *dst = RTC_ALARM_STATUS_OFF;
            }
        }
        break;
        case RTC_SEQ_GET_ALARM_PARAM:
        {
            RTCAlarmParam *dst = (RTCAlarmParam *)(rtcWork.buffer[0]);
            RTCRawAlarm *src = &(rtcRawData->a.alarm);

            dst->week = (RTCWeek)(src->week);
            dst->hour = RtcBCD2HEX_0200e878(src->hour);
            dst->minute = RtcBCD2HEX_0200e878(src->minute);
            dst->enable = RTC_ALARM_ENABLE_NONE;
            if (src->we)
                dst->enable += RTC_ALARM_ENABLE_WEEK;
            if (src->he)
                dst->enable += RTC_ALARM_ENABLE_HOUR;
            if (src->me)
                dst->enable += RTC_ALARM_ENABLE_MINUTE;
        }
        break;
        case RTC_SEQ_SET_ALARM1_STATUS:
            if (rtcWork.index == 0) {
                RTCRawStatus2 *src = &(rtcRawData->a.status2);

                if (*(RTCAlarmStatus *)(rtcWork.buffer[0]) == RTC_ALARM_STATUS_ON) {
                    if (src->intr_mode != RTC_INTERRUPT_MODE_ALARM) {
                        rtcWork.index++;
                        src->intr_mode = RTC_INTERRUPT_MODE_ALARM;
                        if (!RTCi_WriteRawStatus2Async_0200e908()) {
                            rtcWork.index = 0;
                            result = RTC_RESULT_SEND_ERROR;
                        }
                    }
                } else {
                    if (src->intr_mode != RTC_INTERRUPT_MODE_NONE) {
                        rtcWork.index++;
                        src->intr_mode = RTC_INTERRUPT_MODE_NONE;
                        if (!RTCi_WriteRawStatus2Async_0200e908()) {
                            rtcWork.index = 0;
                            result = RTC_RESULT_SEND_ERROR;
                        }
                    }
                }
            } else {
                rtcWork.index = 0;
            }
            break;
        case RTC_SEQ_SET_ALARM2_STATUS:
            if (rtcWork.index == 0) {
                RTCRawStatus2 *src = &(rtcRawData->a.status2);

                if (*(RTCAlarmStatus *)(rtcWork.buffer[0]) == RTC_ALARM_STATUS_ON) {
                    if (!src->intr2_mode) {
                        rtcWork.index++;
                        src->intr2_mode = 1;
                        if (!RTCi_WriteRawStatus2Async_0200e908()) {
                            rtcWork.index = 0;
                            result = RTC_RESULT_SEND_ERROR;
                        }
                    }
                } else {
                    if (src->intr2_mode) {
                        rtcWork.index++;
                        src->intr2_mode = 0;
                        if (!RTCi_WriteRawStatus2Async_0200e908()) {
                            rtcWork.index = 0;
                            result = RTC_RESULT_SEND_ERROR;
                        }
                    }
                }
            } else {
                rtcWork.index = 0;
            }
            break;
        case RTC_SEQ_SET_ALARM1_PARAM:
        case RTC_SEQ_SET_ALARM2_PARAM:
        case RTC_SEQ_SET_HOUR_FORMAT:
        case RTC_SEQ_SET_REG_STATUS2:
        case RTC_SEQ_SET_REG_ADJUST:
            break;
        default:
            result = RTC_RESULT_INVALID_COMMAND;
            rtcWork.index = 0;
        }
    } else {
        rtcWork.index = 0;

        switch (pxiresult) {
        case RTC_PXI_RESULT_INVALID_COMMAND:
            result = RTC_RESULT_INVALID_COMMAND;
            break;
        case RTC_PXI_RESULT_ILLEGAL_STATUS:
            result = RTC_RESULT_ILLEGAL_STATUS;
            break;
        case RTC_PXI_RESULT_BUSY:
            result = RTC_RESULT_BUSY;
            break;
        case RTC_PXI_RESULT_FATAL_ERROR:
        default:
            result = RTC_RESULT_FATAL_ERROR;
        }
    }

    if (rtcWork.index == 0) {
        if (rtcWork.lock != RTC_LOCK_OFF) {
            rtcWork.lock = RTC_LOCK_OFF;
        }

        if (rtcWork.callback) {
            callback = rtcWork.callback;
            rtcWork.callback = NULL;
            callback(result, rtcWork.callbackArg);
        }
    }
}
