#include "nitro/types.h"

typedef struct FSArchive {
    u32 name;
    struct FSArchive *next;
    void *list;
    u8 queue[8];
    u32 flag;
} FSArchive;

extern u32 func_02004938(void);
extern void func_0200494c(u32 state);
extern void SleepCurrentThread_02002aa8(void *queue);

static inline BOOL IsArchiveSuspended(volatile const FSArchive *arc) {
    return (arc->flag & 8) ? TRUE : FALSE;
}

static inline void WaitConditionOff(volatile const u32 *flag, u32 bit, void *queue) {
    u32 savedState = func_02004938();
    while ((*flag & bit) != 0) {
        SleepCurrentThread_02002aa8(queue);
    }
    func_0200494c(savedState);
}

BOOL FS_SuspendArchive_0200b08c(FSArchive *arc) {
    BOOL result;
    u32 savedState = func_02004938();
    result = !IsArchiveSuspended(arc);
    if (result) {
        if ((arc->flag & 0x10) == 0) {
            arc->flag |= 8;
        } else {
            arc->flag |= 0x40;
            WaitConditionOff(&arc->flag, 0x40, arc->queue);
        }
    }
    func_0200494c(savedState);
    return result;
}
