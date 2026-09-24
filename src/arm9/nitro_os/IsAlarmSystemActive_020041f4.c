/* Returns whether the shared alarm scheduler is active.
 * Reconstructed from BK9E instructions using the verified CC0 alarm layout. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long OSTick;
typedef void (*OSAlarmHandler)(void *);
typedef struct OSAlarm {OSAlarmHandler handler; void *arg; u32 tag; OSTick fire; struct OSAlarm *prev,*next; OSTick period,start;} OSAlarm;
typedef struct {u16 active,padding; OSAlarm *head,*tail;} AlarmQueue;
extern AlarmQueue alarmQueue;
extern int OS_DisableInterrupts(void);
extern int OS_RestoreInterrupts(int state);
extern void OS_Terminate(void);
extern OSTick OS_GetTick(void);
extern void InsertAlarmByDeadline(OSAlarm *alarm, OSTick fire);
extern void SetAlarmTimer(OSAlarm *alarm);
extern void ReleaseAlarmTimer(int timer);
u16 IsAlarmSystemActive(void) {return alarmQueue.active;}
