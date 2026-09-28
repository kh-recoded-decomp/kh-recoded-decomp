/* The real-time clock, as the library sources declare them (the NitroSDK / NitroSystem names). */
#ifndef NITRO_RTC_H
#define NITRO_RTC_H

#include "nitro/types.h"

struct RTCAlarmParam;
struct RTCDate;
struct RTCRawAdjust;
struct RTCRawAlarm;
union RTCRawData;
struct RTCRawDate;
struct RTCRawFree;
struct RTCRawPulse;
struct RTCRawStatus1;
struct RTCRawStatus2;
struct RTCRawTime;
struct RTCTime;
struct RTCWork;

typedef enum RTCResult {
    RTC_RESULT_SUCCESS = 0,
    RTC_RESULT_BUSY,
    RTC_RESULT_ILLEGAL_PARAMETER,
    RTC_RESULT_SEND_ERROR,
    RTC_RESULT_INVALID_COMMAND,
    RTC_RESULT_ILLEGAL_STATUS,
    RTC_RESULT_FATAL_ERROR,
    RTC_RESULT_MAX
} RTCResult;

typedef void (*RTCCallback) (RTCResult result, void * arg);

typedef int RTCWeek;

typedef struct RTCDate {
    u32 year;                     /* 0x00: since 2000 */
    u32 month;                    /* 0x04 */
    u32 day;                      /* 0x08 */
    RTCWeek week;                 /* 0x0c */
} RTCDate;

typedef int RTCPxiResult;

typedef int RTCAlarmStatus;

typedef void (*RTCInterrupt)(void);

enum { RTC_PXI_RESULT_SUCCESS = 0, RTC_PXI_RESULT_INVALID_COMMAND, RTC_PXI_RESULT_ILLEGAL_STATUS,
       RTC_PXI_RESULT_BUSY, RTC_PXI_RESULT_FATAL_ERROR };

enum { RTC_ALARM_STATUS_OFF = 0, RTC_ALARM_STATUS_ON, RTC_ALARM_STATUS_MAX };

enum { RTC_LOCK_OFF = 0, RTC_LOCK_ON, RTC_LOCK_MAX };

typedef enum RTCSequence {
    RTC_SEQ_GET_DATE = 0, RTC_SEQ_GET_TIME, RTC_SEQ_GET_DATETIME, RTC_SEQ_SET_DATE, RTC_SEQ_SET_TIME,
    RTC_SEQ_SET_DATETIME, RTC_SEQ_GET_ALARM1_STATUS, RTC_SEQ_GET_ALARM2_STATUS, RTC_SEQ_GET_ALARM_PARAM,
    RTC_SEQ_SET_ALARM1_STATUS, RTC_SEQ_SET_ALARM2_STATUS, RTC_SEQ_SET_ALARM1_PARAM, RTC_SEQ_SET_ALARM2_PARAM,
    RTC_SEQ_SET_HOUR_FORMAT, RTC_SEQ_SET_REG_STATUS2, RTC_SEQ_SET_REG_ADJUST, RTC_SEQ_MAX
} RTCSequence;

#define RTC_ALARM_ENABLE_NONE       0x0000

#define RTC_ALARM_ENABLE_WEEK       0x0001

#define RTC_ALARM_ENABLE_HOUR       0x0002

#define RTC_ALARM_ENABLE_MINUTE     0x0004

#define RTC_INTERRUPT_MODE_NONE     0x0

#define RTC_INTERRUPT_MODE_ALARM    0x4

#define RTC_PXI_COMMAND_MASK        0x00007f00

#define RTC_PXI_COMMAND_SHIFT       8

#define RTC_PXI_RESULT_MASK         0x000000ff

#define RTC_PXI_RESULT_SHIFT        0

#define RTC_PXI_COMMAND_INTERRUPT   0x30

typedef struct RTCTime { u32 hour; u32 minute; u32 second; } RTCTime;

typedef struct RTCAlarmParam { RTCWeek week; u32 hour; u32 minute; u32 enable; } RTCAlarmParam;

typedef struct RTCRawDate {
    u32 year :8;
    u32 month :5;
    u32 dummy0 :3;
    u32 day :6;
    u32 dummy1 :2;
    u32 week :3;
    u32 dummy2 :5;
} RTCRawDate;

typedef struct RTCRawTime {
    u32 hour :6;
    u32 afternoon :1;
    u32 dummy0 :1;
    u32 minute :7;
    u32 dummy1 :1;
    u32 second :7;
    u32 dummy2 :9;
} RTCRawTime;

typedef struct RTCRawStatus1 {
    u16 reset :1;
    u16 format :1;
    u16 dummy0 :2;
    u16 intr1 :1;
    u16 intr2 :1;
    u16 bld :1;
    u16 poc :1;
    u16 dummy1 :8;
} RTCRawStatus1;

typedef struct RTCRawStatus2 {
    u16 intr_mode :4;
    u16 dummy0 :2;
    u16 intr2_mode :1;
    u16 test :1;
    u16 dummy1 :8;
} RTCRawStatus2;

typedef struct RTCRawAlarm {
    u32 week :3;
    u32 dummy0 :4;
    u32 we :1;
    u32 hour :6;
    u32 afternoon :1;
    u32 he :1;
    u32 minute :7;
    u32 me :1;
    u32 dummy2 :8;
} RTCRawAlarm;

typedef struct RTCRawPulse { u32 pulse :5; u32 dummy :27; } RTCRawPulse;

typedef struct RTCRawAdjust { u32 adjust :8; u32 dummy :24; } RTCRawAdjust;

typedef struct RTCRawFree { u32 free :8; u32 dummy :24; } RTCRawFree;

typedef union RTCRawData {
    struct {
        RTCRawDate date;
        RTCRawTime time;
    } t;
    struct {
        RTCRawStatus1 status1;
        RTCRawStatus2 status2;
        union {
            RTCRawPulse pulse;
            RTCRawAlarm alarm;
            RTCRawAdjust adjust;
            RTCRawFree free;
        };
    } a;
    u32 words[2];
    u16 halfs[4];
    u8 bytes[8];
} RTCRawData;

typedef struct RTCWork {
    u32 lock;                     /* 0x00 */
    RTCCallback callback;         /* 0x04 */
    void *buffer[2];              /* 0x08 */
    void *callbackArg;            /* 0x10 */
    u32 sequence;                 /* 0x14 */
    u32 index;                    /* 0x18 */
    RTCInterrupt interrupt;       /* 0x1c */
    RTCResult commonResult;       /* 0x20 */
} RTCWork;

#endif
