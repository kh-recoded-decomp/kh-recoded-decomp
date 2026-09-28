#ifndef NITRO_OS_H
#define NITRO_OS_H

#include "nitro/os_types.h"

#include "nitro/types.h"
#include "nitro/hw.h"
#include "nitro/cp.h"

struct HeapDesc;
struct OSContext;
struct OSLockWord;
struct OSMessageQueue;
struct OSMutex;
struct OSThread;
struct OSThreadInfo;
struct OSiAlarm;
struct OSiAlarmQueue;
struct OSiExContext;
struct OSiExceptionStatics;
struct OSiThreadInfoPrefix;
struct _OSMutexLink;
struct _OSMutexQueue;
struct _OSThread;
struct _OSThreadLink;
struct _OSThreadQueue;

enum {
    OS_IE_CARD_DATA = 1 << 19
};

typedef void *OSMessage;

#define OS_LOCK_ID_ERROR (-3)

#define OS_Panic(...) OS_Terminate()

#define OS_TPanic(...) OS_Terminate()

struct OSiThreadInfoPrefix {
    u32 initialized;
    void *current_thread;
};

typedef struct OSContext {
    u32 cpsr;
    u32 r[13];
    u32 sp;
    u32 lr;
    u32 pc_plus4;
    u32 sp_svc;
    CPContext cp_context;
} OSContext;

typedef struct _OSThread OSThread;

typedef struct _OSThreadQueue OSThreadQueue;

typedef struct _OSThreadLink OSThreadLink;

typedef struct _OSMutexQueue OSMutexQueue;

typedef struct _OSMutexLink OSMutexLink;

typedef struct OSMutex OSMutex;

typedef struct OSiAlarm OSAlarm;

struct _OSThreadQueue {
        OSThread * head;
        OSThread * tail;
    };

struct _OSThreadLink {
        OSThread * prev;
        OSThread * next;
    };

struct _OSMutexQueue {
        OSMutex * head;
        OSMutex * tail;
    };

struct _OSMutexLink {
        OSMutex * next;
        OSMutex * prev;
    };

typedef enum {
    OS_THREAD_STATE_WAITING       = 0,
    OS_THREAD_STATE_READY         = 1,
    OS_THREAD_STATE_TERMINATED    = 2
} OSThreadState;

typedef void (*OSThreadDestructor) (void *);

typedef struct OSContext OSContext;

struct _OSThread {
    OSContext context;
    OSThreadState state;
    OSThread * next;
    u32 id;
    u32 priority;
    void * profiler;
    OSThreadQueue * queue;
    OSThreadLink link;
    OSMutex * mutex;
    OSMutexQueue mutexQueue;
    u32 stackTop;
    u32 stackBottom;
    u32 stackWarningOffset;
    OSThreadQueue joinQueue;
    void * specific[3 ];
    OSAlarm * alarmForSleep;
    OSThreadDestructor destructor;
    void * userParameter;
    int systemErrno;
};

struct OSMutex {
    OSThreadQueue queue;
    OSThread * thread;
    s32 count;
    OSMutexLink link;
};

typedef void (*OSAlarmHandler) (void *);

struct OSiAlarm {
    OSAlarmHandler handler;
    void * arg;
    u32 tag;
    OSTick fire;
    OSAlarm * prev;
    OSAlarm * next;
    OSTick period;
    OSTick start;
};

typedef u32 OSIrqMask;

#define OS_IME_ENABLE 1

#define OS_IE_SPFIFO_RECV (1UL << 18)

#define OS_IE_GXFIFO                (1UL << 21)

typedef void (*OSIrqFunction)(void *arg);

typedef unsigned int OSIntrMode_Irq;

#define OSi_TCM_REGION_BASE_MASK     0xfffff000

typedef unsigned int OSProcMode;

#define OS_CONTEXT_CPSR              0

#define OS_CONTEXT_LR                60

#define OS_CONTEXT_PC_PLUS4          64

#define OS_CONTEXT_R0                4

#define OS_CONTEXT_R1                8

#define OS_CONTEXT_R10               44

#define OS_CONTEXT_R11               48

#define OS_CONTEXT_R12               52

#define OS_CONTEXT_R2                12

#define OS_CONTEXT_R3                16

#define OS_CONTEXT_R4                20

#define OS_CONTEXT_R5                24

#define OS_CONTEXT_R6                28

#define OS_CONTEXT_R7                32

#define OS_CONTEXT_R8                36

#define OS_CONTEXT_R9                40

#define OS_CONTEXT_SP                56

#define OS_CONTEXT_SP_SVC            68

#define OS_CONTEXT_CP_CONTEXT        72

typedef struct OSiExContext {
    OSContext context;
    u32 cp15;
    u32 spsr;
    u32 exinfo;
    u32 debug[4];
} OSiExContext;

#define OS_CONTEXT_R13               56

#define OS_CONTEXT_R14               60

typedef struct OSiExContext OSiExContext;

typedef void (*OSExceptionHandler)(void *context, void *arg);

typedef struct OSiExceptionStatics {
    void *debuggerHandler;
    void *userExceptionHandlerArg;
    OSExceptionHandler userExceptionHandler;
} OSiExceptionStatics;

typedef int OSHeapHandle;

typedef struct HeapDesc HeapDesc;

typedef struct {
    volatile OSHeapHandle currentHeap;
    int numHeaps;
    void *arenaStart;
    void *arenaEnd;
    HeapDesc *heapArray;
} OSHeapInfo;

#define OSi_CONSOLE_NOT_DETECT 0xffffffff

#define OS_IRQ_TABLE_MAX 22

typedef void (*OSThreadFunc)(void *pArg);

#define OSi_STACK_MAGIC_HIGH 0xfddb597du

#define OSi_STACK_MAGIC_LOW  0x7bf9dd5bu

typedef struct OSThreadInfo {
    u16 isNeedRescheduling;
    u16 irqDepth;
    OSThread * current;
    OSThread * list;
    void * switchCallback;
} OSThreadInfo;

typedef enum {
    OS_TIMER_0 = 0,
    OS_TIMER_1 = 1,
    OS_TIMER_2 = 2,
    OS_TIMER_3 = 3
} OSTimer;

#define OSi_ALARM_TIMER OS_TIMER_1

#define OS_CONSOLE_SIZE_MASK 0x00000003

#define OS_CONSOLE_SIZE_4MB  0x00000001

#define OSi_SYS_STACKSIZE ((s32)SDK_SYS_STACKSIZE)

#define OSi_IRQ_STACKSIZE ((s32)SDK_IRQ_STACKSIZE)

#define OSi_MAIN_ARENA_HI_DEFAULT   HW_MAIN_MEM_MAIN_END

#define OSi_MAINEX_ARENA_HI_DEFAULT HW_MAIN_MEM_DEBUGGER

#define OSi_DTCM_ARENA_LO_DEFAULT   ((u32)SDK_SECTION_ARENA_DTCM_START)

#define OSi_WRAM_MAIN_ARENA_HI_DEFAULT HW_WRAM

#define OS_THREAD_LAUNCHER_PRIORITY 16

#define OS_THREAD_PRIORITY_MAX 31

#define OS_THREAD_SPECIFIC_MAX 3

struct OSThread {
    u8 context[0x64];
    OSThreadState state;
    OSThread *next;
    u32 id;
    u32 priority;
    void *profiler;
    OSThreadQueue *queue;
    OSThreadLink link;
    void *mutex;
    OSMutexQueue mutexQueue;
    u32 stackTop;
    u32 stackBottom;
    u32 stackWarningOffset;
    OSThreadQueue joinQueue;
    void *specific[OS_THREAD_SPECIFIC_MAX];
    void *alarmForSleep;
    void (*destructor)(void *);
    void *userParameter;
    int systemErrno;
};

#define OSi_IDLE_CHECKNUM_SIZE (sizeof(u32) * 2 + HW_SVC_STACK_SIZE)

#define OSi_IDLE_SVC_SIZE (sizeof(u32) * 32)

#define OSi_IDLE_THREAD_STACK_SIZE (OSi_IDLE_CHECKNUM_SIZE + OSi_IDLE_SVC_SIZE)

#define OSi_STACK_CHECKNUM_BOTTOM 0xfddb597dUL

#define OSi_STACK_CHECKNUM_TOP    0x7bf9dd5bUL

#define OSi_LAUNCHER_STACK_LO_DEFAULT SDK_SECTION_ARENA_DTCM_START

#define OSi_LAUNCHER_STACK_HI_MAX (HW_DTCM_SVC_STACK_ADDR - OSi_IRQ_STACKSIZE)

#define OSi_LAUNCHER_STACK_BOTTOM (HW_DTCM_SVC_STACK_ADDR - OSi_IRQ_STACKSIZE)

#define OSi_SYSTEMWORK_THREADINFO_MAINP (*(OSThreadInfo **)0x027fffa0)

#define OS_SetSwitchThreadCallback OS_SetIrqWorkField30

typedef struct {
    OSIrqFunction pfnHandler;
    unsigned int bKeepEnabled;
    void *pArg;
} OSiIrqSlot;

#define OS_LOW_ENTROPY_DATA_SIZE 32

typedef struct {
    u8 bootCheckInfo[0x20];
    u32 resetParameter;
    u8 padding5[0x8];
    u32 romBaseOffset;
    u8 cartridgeModuleInfo[12];
    u32 vblankCount;
    u8 wmBootBuf[0x40];
    u8 nvramUserInfo[0x100];
    u8 isd_reserved1[0x20];
    u8 arenaInfo[0x48];
    u8 real_time_clock[8];
    u32 dmaClearBuf[4];
    u8 rom_header[0x160];
    u8 isd_reserved2[32];
    u32 pxiSignalParam[2];
    u32 pxiHandleChecker[2];
    u32 mic_last_address;
    u16 mic_sampling_data;
    u16 wm_callback_control;
    u16 wm_rssi_pool;
    u8 ctrdg_SetModuleInfoFlag;
    u8 ctrdg_IsExisting;
    u32 component_param;
    void *threadinfo_mainp;
    void *threadinfo_subp;
    u16 button_XY;
    u8 touch_panel[4];
    u16 autoloadSync;
} OSSystemWork;

#define OS_GetSystemWork() ((OSSystemWork *)HW_MAIN_MEM_SYSTEM)

#define OSi_TICK_TIMER OS_TIMER_0

#define OS_IE_TIMER0 (1UL << 3)

#define OSi_TICK_IE_TIMER OS_IE_TIMER0

#define OS_InitPrintServer() ((void)0)

#define OSi_LockIdFlags  ((u32 *)0x027fffb0)

#define OS_LOCKID_INIT   0x7e

#define OS_LOCKID_ERROR  0x7f

typedef struct OSLockWord {
    u16 lockFlag;
    u16 extension;
} OSLockWord;

typedef void (*OSLockCallback)(void);

#define OSi_CardLock ((OSLockWord *)0x027fffe0)

#define OSi_GetCurrentThread() (*OSi_CurrentThreadPtr)

#define OSi_IrqCheckFlags (*(volatile u32 *)(DTCM + 0x3ff8))

struct OSiAlarmQueue {
    OSAlarm *head;
    OSAlarm *tail;
};

#define OS_TIMER_PRESCALER_64 (1UL << 0)

#define OSi_ALARM_TIMERCONTROL    (REG_OS_TM0CNT_H_E_MASK | REG_OS_TM0CNT_H_I_MASK | OS_TIMER_PRESCALER_64)

#define OSi_ALARM_IE_TIMER        (1UL << 4)

#define OSi_TICK_TIMERCONTROL  (REG_OS_TM0CNT_H_E_MASK | REG_OS_TM0CNT_H_I_MASK | OS_TIMER_PRESCALER_64)

#define OS_IRQ_DMA0_BIT 8

#define OS_IRQ_TIMER0_BIT  3

#define OSi_IRQ_STACK_BOTTOM            HW_DTCM_IRQ_STACK_END

#define OSi_IRQ_STACK_TOP               (OSi_IRQ_STACK_BOTTOM - (u32)SDK_IRQ_STACKSIZE)

#define OSi_IRQ_STACK_CHECKNUM_BOTTOM   0xfddb597dUL

#define OSi_IRQ_STACK_CHECKNUM_TOP      0x7bf9dd5bUL

typedef struct {
    u8 reserved[0x3fc0];
    u8 sysrv[0x38];
    vu32 intr_check;
} OSDtcm;

typedef void (*OSSwitchThreadCallback)(void *from, void *to);

#define OS_GetSystemWork_real_time_clock() ((u8 *)HW_RTC_BUF)

#define OS_IE_FIFO_RECV (1UL << 18)

#define OS_IE_CARD_IREQ (1UL << 20)

#define OS_IME_DISABLE 0

#define OS_MilliSecondsToTicks(msec) ((msec) * (HW_SYSTEM_CLOCK / 64) / 1000)

#define OS_GetSystemWork_nvramUserInfo() ((void *)HW_NVRAM_USER_INFO)

#define OS_MESSAGE_NOBLOCK      0

#define OS_MESSAGE_BLOCK        1

#define OS_GetVBlankCount() (*(volatile u32 *)0x027ffc3c)

typedef struct OSMessageQueue OSMessageQueue;

typedef enum {
    OS_ARENA_MAIN            = 0,
    OS_ARENA_MAIN_SUBPRIV    = 1,
    OS_ARENA_MAINEX          = 2,
    OS_ARENA_ITCM            = 3,
    OS_ARENA_DTCM            = 4,
    OS_ARENA_SHARED          = 5,
    OS_ARENA_WRAM_MAIN       = 6,
    OS_ARENA_WRAM_SUB        = 7,
    OS_ARENA_WRAM_SUBPRIV    = 8,
    OS_ARENA_MAX             = 9
} OSArenaId;

typedef struct {
    void (*func) (void *);
    u32 enable;
    void * arg;
} OSIrqCallbackInfo;

#define OSi_Warning(file, line, ...) ((void)0)

struct OSMessageQueue {
    OSThreadQueue queueSend;
    OSThreadQueue queueReceive;
    OSMessage * msgArray;
    s32 msgCount;
    s32 firstIndex;
    s32 usedCount;
};

#endif
