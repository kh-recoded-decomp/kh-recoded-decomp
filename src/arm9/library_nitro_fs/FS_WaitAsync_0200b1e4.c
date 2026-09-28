#include "nitro/types.h"

typedef struct FSFile {
    struct FSFile *next;
    void *userdata;
    void *arc;
    u32 stat;
    void *argument;
    int error;
    u8 queue[8];
} FSFile;

extern u32 func_02004938(void);
extern void func_0200494c(u32 state);
extern void SleepCurrentThread_02002aa8(void *queue);
extern void AdvanceCommandQueue_0200a8ac(FSFile *file);

static inline BOOL IsFileBusy(volatile const FSFile *file) {
    return (file->stat & 1) ? TRUE : FALSE;
}

static inline BOOL IsFileSucceeded(volatile const FSFile *file) {
    return (file->error == 0) ? TRUE : FALSE;
}

static inline void WaitConditionOff(volatile const u32 *flag, u32 bit, void *queue) {
    u32 savedState = func_02004938();
    while ((*flag & bit) != 0) {
        SleepCurrentThread_02002aa8(queue);
    }
    func_0200494c(savedState);
}

BOOL FS_WaitAsync_0200b1e4(FSFile *file) {
    BOOL isOwner = FALSE;
    {
        u32 savedState = func_02004938();
        if (IsFileBusy(file)) {
            isOwner = !(file->stat & 0x44);
            if (isOwner) {
                file->stat |= 4;
            }
        }
        func_0200494c(savedState);
    }
    if (isOwner) {
        AdvanceCommandQueue_0200a8ac(file);
    } else {
        WaitConditionOff(&file->stat, 1, file->queue);
    }
    return IsFileSucceeded(file);
}
