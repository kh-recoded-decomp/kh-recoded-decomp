#ifndef NITRO_CTRDG_H
#define NITRO_CTRDG_H

#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nitro/hw.h"
#include "nitro/mi.h"

struct CTRDGLockByProc;
struct CTRDGRomCycle;
struct CTRDGWork;

#define CTRDG_SYSROM9_NINLOGO_ADR       0xffff0020

#define CTRDG_IS_ROM_CODE               0x96

#define CTRDG_PXI_COMMAND_PARAM_SHIFT   6

#define CTRDG_PXI_COMMAND_INIT_MODULE_INFO 0x0001

typedef struct {
    u32 startAddress;
    u8 nintendoLogo[0x9c];
    char titleName[12];
    u32 gameCode;
    u16 makerCode;
    u8 isRomCode;
    u8 machineCode;
    u8 deviceType;
    u8 exLsiID[3];
    u8 reserved_A[4];
    u8 softVersion;
    u8 complement;
    u16 moduleID;
} CTRDGHeader;

typedef struct {
    union {
        struct {
            u8 bitID;
            u8 numberID :5;
            u8 :2;
            u8 disableExLsiID :1;
        };
        u16 raw;
    };
} CTRDGModuleID;

typedef struct {
    CTRDGModuleID moduleID;
    u8 exLsiID[3];
    u8 isAgbCartridge :1;
    u8 detectPullOut :1;
    u8 :0;
    u16 makerCode;
    u32 gameCode;
} CTRDGModuleInfo;

typedef struct CTRDGRomCycle {
    MICartridgeRomCycle1st c1;
    MICartridgeRomCycle2nd c2;
} CTRDGRomCycle;

typedef struct CTRDGLockByProc {
    BOOL locked;
    OSIntrMode irq;
} CTRDGLockByProc;

typedef struct CTRDGWork {
    vu16 subpInitialized;
    u16 lockID;
} CTRDGWork;

#define CTRDGi_GetHeaderAddr()          ((CTRDGHeader *)HW_CTRDG_ROM)

#define CTRDGi_GetModuleIDImageAddr()   ((u16 *)(HW_CTRDG_ROM + 0x0001fffe))

#define CTRDGi_GetModuleInfoAddr()      ((CTRDGModuleInfo *)HW_CTRDG_MODULE_INFO_BUF)

#define CTRDG_PXI_COMMAND_TERMINATE 0x0002

#endif
