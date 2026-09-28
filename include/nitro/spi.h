/* SPI devices: touch panel, power management, microphone, as the library sources declare them (the NitroSDK / NitroSystem names). */
#ifndef NITRO_SPI_H
#define NITRO_SPI_H

#include "nitro/types.h"
#include "nitro/os.h"

struct NvTpData;
struct PMiSleepCallbackInfo;
struct PXIContext;
union SPITpData;
struct TPSample;
struct TPState;

#define PM_RESULT_SUCCESS 0

#define SPI_PXI_RESULT_EXCLUSIVE 0x0004

typedef enum {
    TP_REQUEST_COMMAND_SAMPLING         = 0x0,
    TP_REQUEST_COMMAND_AUTO_ON          = 0x1,
    TP_REQUEST_COMMAND_AUTO_OFF         = 0x2,
    TP_REQUEST_COMMAND_SET_STABILITY    = 0x3,
    TP_REQUEST_COMMAND_AUTO_SAMPLING    = 0x10
} TPRequestCommand;

typedef enum {
    TP_RESULT_SUCCESS = 0,
    TP_RESULT_INVALID_PARAMETER,
    TP_RESULT_ILLEGAL_STATUS,
    TP_RESULT_EXCLUSIVE,
    TP_RESULT_PXI_BUSY
} TPRequestResult;

typedef void (*TPRecvCallback) (TPRequestCommand command, TPRequestResult result, u16 index);

typedef enum MICResult {
    MIC_RESULT_SUCCESS = 0,
    MIC_RESULT_BUSY,
    MIC_RESULT_ILLEGAL_PARAMETER,
    MIC_RESULT_SEND_ERROR,
    MIC_RESULT_INVALID_COMMAND,
    MIC_RESULT_ILLEGAL_STATUS,
    MIC_RESULT_FATAL_ERROR,
    MIC_RESULT_MAX
} MICResult;

typedef void (*MICCallback) (MICResult result, void * arg);

typedef void (*PMCallback) (u32 result, void * arg);

typedef enum {
    PM_LCD_POWER_OFF = 0,
    PM_LCD_POWER_ON = 1
} PMLCDPower;

typedef void (*PMSleepCallback) (void *);

typedef struct PMiSleepCallbackInfo PMSleepCallbackInfo;

struct PMiSleepCallbackInfo {
    PMSleepCallback callback;
    void * arg;
    PMSleepCallbackInfo * next;
};

#define PMIC_REG_NUMS 5

#define PM_RESULT_ERROR 2

#define SPI_PXI_RESULT_COMMAND_MASK         0x00007f00

#define SPI_PXI_RESULT_COMMAND_SHIFT        8

#define SPI_PXI_RESULT_DATA_MASK            0x000000ff

#define SPI_PXI_RESULT_DATA_SHIFT           0

#define SPI_PXI_COMMAND_PM_SYNC             0x0060

#define SPI_PXI_COMMAND_PM_SLEEP_END        0x0062

#define SPI_PXI_COMMAND_PM_GET_BLINK        0x0067

#define SPI_PXI_COMMAND_PM_REG0VALUE        0x0070

#define SPI_PXI_COMMAND_PM_REG4VALUE        0x0074

typedef struct {
    BOOL lock;                    /* 0x00 */
    PMCallback callback;          /* 0x04 */
    void *callbackArg;            /* 0x08 */
    void *work;                   /* 0x0c */
} PMiWork;

typedef struct {
    u16 flag;                     /* 0x00 */
    u16 pad;
    u16 *buffer;                  /* 0x04 */
} PMData16;

typedef u32 PMWakeUpTrigger;

typedef u32 PMLogic;

#define PM_SUCCESS 0

#define PM_TRIGGER_CARD             (1 << 3)

#define PM_TRIGGER_CARTRIDGE        (1 << 4)

#define PM_BACKLIGHT_RECOVER_TOP_SHIFT      5

#define PM_BACKLIGHT_RECOVER_BOTTOM_SHIFT   6

#define PMi_LCD_SLEEP_WAIT_MSEC  110

#define PMi_LCD_SLEEP_WAIT_TICK  (OS_MilliSecondsToTicks(PMi_LCD_SLEEP_WAIT_MSEC) * (64 * 2))

#define PMi_LCD_POWER_WAIT_MSEC  150

#define PMi_LCD_POWER_WAIT_TICK  (OS_MilliSecondsToTicks(PMi_LCD_POWER_WAIT_MSEC) * (64 * 2))

enum { PM_UTIL_DUMMY = 0, PM_UTIL_LED_ON, PM_UTIL_LED_BLINK_HIGH_SPEED, PM_UTIL_LED_BLINK_LOW_SPEED,
       PM_UTIL_LCD1_BACKLIGHT_ON, PM_UTIL_LCD1_BACKLIGHT_OFF, PM_UTIL_LCD2_BACKLIGHT_ON, PM_UTIL_LCD2_BACKLIGHT_OFF,
       PM_UTIL_LCD12_BACKLIGHT_ON, PM_UTIL_LCD12_BACKLIGHT_OFF, PM_UTIL_SOUND_POWER_ON, PM_UTIL_SOUND_POWER_OFF,
       PM_UTIL_SOUND_VOL_CTRL_ON, PM_UTIL_SOUND_VOL_CTRL_OFF, PM_UTIL_FORCE_POWER_OFF, PM_UTIL_FORCE_POWER_ON };

#define PMIC_CTL_BKLT1 (1 << 2)

#define PMIC_CTL_BKLT2 (1 << 3)

typedef enum {
    PM_BACKLIGHT_OFF = 0,
    PM_BACKLIGHT_ON = 1
} PMBackLightSwitch;

typedef enum {
    PM_LCD_TOP = 0,
    PM_LCD_BOTTOM = 1,
    PM_LCD_ALL = 2
} PMLCDTarget;

#define PM_INVALID_COMMAND 0xffff

typedef enum {
    PM_LED_NONE = 0,
    PM_LED_ON = 1,
    PM_LED_BLINK_LOW = 2,
    PM_LED_BLINK_HIGH = 3
} PMLEDStatus;

typedef struct PXIContext {
    unsigned char reserved_00[0x1c];
    u32 locked;
    PMCallback callback;
    void *callbackArgument;
} PXIContext;

typedef enum {
    PM_AMP_OFF = 0,
    PM_AMP_ON = 1
} PMAmpSwitch;

enum { TP_STATE_READY = 0, TP_STATE_SAMPLING, TP_STATE_AUTO_SAMPLING, TP_STATE_AUTO_WAIT_END };

#define SPI_PXI_END_BIT                     0x01000000

#define SPI_PXI_DATA_MASK                   0x0000ffff

#define SPI_PXI_COMMAND_TP_SAMPLING         0x0000

#define SPI_PXI_COMMAND_TP_AUTO_ON          0x0001

#define SPI_PXI_COMMAND_TP_AUTO_OFF         0x0002

#define SPI_PXI_COMMAND_TP_AUTO_SAMPLING    0x0010

#define SPI_PXI_RESULT_SUCCESS              0x0000

#define SPI_PXI_RESULT_INVALID_COMMAND      0x0001

#define SPI_PXI_RESULT_INVALID_PARAMETER    0x0002

#define SPI_PXI_RESULT_ILLEGAL_STATUS       0x0003

#define TP_RAW_MAX  0x1000

#define TP_CALIBRATE_DOT_SCALE_SHIFT        8

#define TP_CALIBRATE_ORIGIN_SCALE_SHIFT     2

typedef struct {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TPData;

typedef struct NvTpData {
    s16 x0;
    s16 y0;
    s16 xDotSize;
    s16 yDotSize;
} TPCalibrateParam;

typedef union SPITpData {
    struct {
        u32 x : 12;
        u32 y : 12;
        u32 touch : 1;
        u32 validity : 2;
        u32 dummy : 5;
    } e;
    u32 raw;
    u8 bytes[4];
    u16 halfs[2];
} SPITpData;

typedef struct {
    s32 x0;
    s32 xDotSize;
    s32 xDotSizeInv;
    s32 y0;
    s32 yDotSize;
    s32 yDotSizeInv;
} TPiCalibrateParam;

struct TPSample {
    u32 xy00;
    u16 touch04;
    u16 validity06;
};

struct TPState {
    u8 pad00[4];
    TPRecvCallback callback04;
    u8 pad08[8];
    u16 index10;
    u16 frequence12;
    struct TPSample *samplingBufs14;
    u16 bufSize18;
    u8 pad1a[0x1e];
    u16 errFlags38;
    u16 commandFlags3a;
};

#endif
