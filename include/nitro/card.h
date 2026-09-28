/* The game card and its backup memory, as the library sources declare them (the NitroSDK / NitroSystem names). */
#ifndef NITRO_CARD_H
#define NITRO_CARD_H

#include "nitro/types.h"
#include "nitro/os.h"

struct CARDBackupSpec;
struct CARDRomStat;
struct CARDiCommandArg;
struct CARDiCommon;

enum {
    CARD_STAT_INIT = (1 << 0),
    CARD_STAT_INIT_CMD = (1 << 1),
    CARD_STAT_BUSY = (1 << 2),
    CARD_STAT_TASK = (1 << 3),
    CARD_STAT_RECV = (1 << 4),
    CARD_STAT_REQ = (1 << 5),
    CARD_STAT_CANCEL = (1 << 6),
    CARD_MASTER_SELECT_ROM = 0x00,
    CARD_MASTER_ENABLE = 0x80,
    CARD_CMD_READ_PAGE = 0xb7,
    CARD_CTRL_CMD_MASK = 0x07000000,
    CARD_CTRL_CMD_PAGE = 0x01000000,
    CARD_CTRL_READ = 0x00000000,
    CARD_CTRL_RESET_HI = 0x20000000,
    CARD_CTRL_START = 0x80000000,
    CARD_CTRL_READY = 0x00800000
};

typedef s32 CARDiOwner;

typedef enum {
    CARD_REQ_INIT = 0,
    CARD_REQ_ACK,
    CARD_REQ_IDENTIFY,
    CARD_REQ_READ_ID,
    CARD_REQ_READ_ROM,
    CARD_REQ_WRITE_ROM,
    CARD_REQ_READ_BACKUP,
    CARD_REQ_WRITE_BACKUP,
    CARD_REQ_PROGRAM_BACKUP,
    CARD_REQ_VERIFY_BACKUP,
    CARD_REQ_ERASE_PAGE_BACKUP,
    CARD_REQ_ERASE_SECTOR_BACKUP,
    CARD_REQ_ERASE_CHIP_BACKUP,
    CARD_REQ_READ_STATUS,
    CARD_REQ_WRITE_STATUS,
    CARD_REQ_ERASE_SUBSECTOR_BACKUP,
    CARD_REQ_MAX
} CARDRequest;

#define CARD_BACKUP_CAPS_READ               (u32)(1 << CARD_REQ_READ_BACKUP)

#define CARD_BACKUP_CAPS_AVAILABLE          (u32)(CARD_BACKUP_CAPS_READ - 1)

#define CARD_BACKUP_CAPS_WRITE              (u32)(1 << CARD_REQ_WRITE_BACKUP)

#define CARD_BACKUP_CAPS_PROGRAM            (u32)(1 << CARD_REQ_PROGRAM_BACKUP)

#define CARD_BACKUP_CAPS_VERIFY             (u32)(1 << CARD_REQ_VERIFY_BACKUP)

#define CARD_BACKUP_CAPS_ERASE_PAGE         (u32)(1 << CARD_REQ_ERASE_PAGE_BACKUP)

#define CARD_BACKUP_CAPS_ERASE_SECTOR       (u32)(1 << CARD_REQ_ERASE_SECTOR_BACKUP)

#define CARD_BACKUP_CAPS_ERASE_CHIP         (u32)(1 << CARD_REQ_ERASE_CHIP_BACKUP)

#define CARD_BACKUP_CAPS_READ_STATUS        (u32)(1 << CARD_REQ_READ_STATUS)

#define CARD_BACKUP_CAPS_WRITE_STATUS       (u32)(1 << CARD_REQ_WRITE_STATUS)

#define CARD_BACKUP_CAPS_ERASE_SUBSECTOR    (u32)(1 << CARD_REQ_ERASE_SUBSECTOR_BACKUP)

#define CARD_BACKUP_TYPE_DEVICE_SHIFT   0

#define CARD_BACKUP_TYPE_DEVICE_MASK    0xFF

#define CARD_BACKUP_TYPE_DEVICE_EEPROM  1

#define CARD_BACKUP_TYPE_DEVICE_FLASH   2

#define CARD_BACKUP_TYPE_DEVICE_FRAM    3

#define CARD_BACKUP_TYPE_SIZEBIT_SHIFT  8

#define CARD_BACKUP_TYPE_SIZEBIT_MASK   0xFF

#define CARD_BACKUP_TYPE_VENDER_SHIFT   16

#define CARD_BACKUP_TYPE_VENDER_MASK    0xFF

#define CARD_THREAD_PRIORITY_DEFAULT    4

typedef void (*CARDCallback)(void *argument);

#define CARD_PXI_COMMAND_TERMINATE 0x0001

typedef enum { CARD_TARGET_NONE, CARD_TARGET_ROM, CARD_TARGET_BACKUP } CARDTargetMode;

#define CARD_ROM_PAGE_SIZE 512

typedef struct CARDiCommandArg {
    int result;                   /* 0x00: CARDResult */
    int type;                     /* 0x04 */
    u32 id;                       /* 0x08 */
    u32 src;                      /* 0x0c */
    u32 dst;                      /* 0x10 */
    u32 len;                      /* 0x14 */
} CARDiCommandArg;

typedef struct CARDiCommon {
    CARDiCommandArg *cmd;         /* 0x00 */
    int command;                  /* 0x04 */
    volatile CARDiOwner lock_owner;   /* 0x08 */
    volatile int lock_ref;        /* 0x0c */
    OSThreadQueue lock_queue[1];  /* 0x10 */
    CARDTargetMode lock_target;   /* 0x18 */
    u32 src;                      /* 0x1c */
    u32 dst;                      /* 0x20 */
    u32 len;                      /* 0x24 */
    u32 dma;                      /* 0x28 */
} CARDiCommon;

typedef struct CARDRomStat {
    void (*read_func)(struct CARDRomStat *);   /* 0x00 */
    u32 ctrl;                     /* 0x04 */
    u8 *cache_page;               /* 0x08 */
    u32 dummy[5];                 /* 0x0c */
    u8 cache_buf[CARD_ROM_PAGE_SIZE];   /* 0x20 */
} CARDRomStat;

#define CARD_DATA_READY         0x00800000

#define CARD_COMMAND_PAGE       0x01000000

#define CARD_COMMAND_ID         0x07000000

#define CARD_COMMAND_MASK       0x07000000

#define CARD_RESET_HI           0x20000000

#define CARD_READ_MODE          0x00000000

#define CARD_START              0x80000000

#define CARD_LATENCY1_MASK      0x00001FFF

#define CARD_ALIGN_HI_BIT(n)     (((u32)(n)) & ~(CARD_ROM_PAGE_SIZE - 1))

typedef void (*CARDFunc)(void *);

struct CARDBackupSpec {
    u32 total_size;
    u32 sector_size;
    u32 page_size;
    u32 address_width;
    u32 program_page;
    u32 write_page;
    u32 write_page_total;
    u32 erase_chip;
    u32 erase_chip_total;
    u32 erase_sector;
    u32 erase_sector_total;
    u32 erase_page;
    u8 initial_status;
    u8 padding_31[3];
    u32 capabilities;
    u8 padding_38[16];
};

typedef enum {
    CARD_RESULT_SUCCESS = 0,
    CARD_RESULT_FAILURE,
    CARD_RESULT_INVALID_PARAM,
    CARD_RESULT_UNSUPPORTED,
    CARD_RESULT_TIMEOUT,
    CARD_RESULT_ERROR,
    CARD_RESULT_NO_RESPONSE,
    CARD_RESULT_CANCELED
} CARDResult;

typedef enum {
    CARD_BACKUP_TYPE_EEPROM_4KBITS = (((1) << 0) | (( 9) << 8) | (( 0) << 16)) ,
    CARD_BACKUP_TYPE_EEPROM_64KBITS = (((1) << 0) | (( 13) << 8) | (( 0) << 16)) ,
    CARD_BACKUP_TYPE_EEPROM_512KBITS = (((1) << 0) | (( 16) << 8) | (( 0) << 16)) ,
    CARD_BACKUP_TYPE_FLASH_2MBITS = (((2) << 0) | (( 18) << 8) | (( 0) << 16)) ,
    CARD_BACKUP_TYPE_FLASH_4MBITS = (((2) << 0) | (( 19) << 8) | (( 0) << 16)) ,
    CARD_BACKUP_TYPE_FLASH_8MBITS = (((2) << 0) | (( 20) << 8) | (( 0) << 16)) ,
    CARD_BACKUP_TYPE_FLASH_16MBITS = (((2) << 0) | (( 21) << 8) | (( 0) << 16)) ,
    CARD_BACKUP_TYPE_FLASH_64MBITS = (((2) << 0) | (( 23) << 8) | (( 0) << 16)) ,
    CARD_BACKUP_TYPE_FRAM_256KBITS = (((3) << 0) | (( 15) << 8) | (( 0) << 16)) ,
    CARD_BACKUP_TYPE_NOT_USE = 0
} CARDBackupType;

typedef enum {
    CARD_REQUEST_MODE_RECV,
    CARD_REQUEST_MODE_SEND,
    CARD_REQUEST_MODE_SEND_VERIFY,
    CARD_REQUEST_MODE_SPECIAL
} CARDRequestMode;

typedef struct {
    u32 offset;
    u32 length;
} CARDRomRegion;

#endif
