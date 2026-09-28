#include "nitro/types.h"

#define FILE_STATUS_CANCEL 0x02
#define FILE_STATUS_SYNC 0x04
#define FILE_STATUS_OPERATING 0x40

#define ARCHIVE_FLAG_SUSPEND 0x08
#define ARCHIVE_FLAG_RUNNING 0x10
#define ARCHIVE_FLAG_CANCELING 0x20
#define ARCHIVE_FLAG_SUSPENDING 0x40

#define RESULT_CANCELED 3
#define COMMAND_ACTIVATE 9
#define COMMAND_IDLE 10

struct FSArchive;

typedef struct FSFile {
    struct FSFile *next;
    void *userdata;
    struct FSArchive *arc;
    u32 stat;
    void *argument;
    int error;
    u8 queue[8];
    u8 pad_20[0x28];
} FSFile;

typedef struct FSArchive {
    u32 name;
    struct FSArchive *next;
    FSFile *list;
    u8 queue[8];
    u32 flag;
} FSArchive;

extern u32 func_02004938(void);
extern void func_0200494c(u32 state);
extern void func_0200a200(FSFile *file, u32 result);
extern int func_0200a2fc(FSFile *file, u32 command);
extern void func_0200b394(FSFile *file);
extern void OS_WakeupThread_02002af8(void *queue);

static inline BOOL IsCanceling(const FSFile *file) {
    return (file->stat & FILE_STATUS_CANCEL) ? TRUE : FALSE;
}

FSFile *FSi_NextCommand_0200a67c(FSArchive *arc, BOOL owner) {
    FSFile *next = NULL;
    {
        u32 savedState = func_02004938();
        if ((arc->flag & ARCHIVE_FLAG_CANCELING) != 0) {
            FSFile *file = arc->list;
            arc->flag &= ~ARCHIVE_FLAG_CANCELING;
            while (file != NULL) {
                FSFile *following = file->next;
                if (IsCanceling(file) != FALSE && (file->stat & FILE_STATUS_OPERATING) == 0) {
                    func_0200a200(file, RESULT_CANCELED);
                    if (following == NULL) {
                        following = arc->list;
                    }
                }
                file = following;
            }
        }
        func_0200494c(savedState);
    }
    {
        u32 savedState = func_02004938();
        if ((arc->flag & ARCHIVE_FLAG_SUSPENDING) == 0 && (arc->flag & ARCHIVE_FLAG_SUSPEND) == 0 && arc->list != NULL) {
            const BOOL start = owner && (arc->flag & ARCHIVE_FLAG_RUNNING) == 0;
            if (start) {
                arc->flag |= ARCHIVE_FLAG_RUNNING;
            }
            func_0200494c(savedState);
            if (start) {
                func_0200a2fc(arc->list, COMMAND_ACTIVATE);
            }
            savedState = func_02004938();
            if (owner || start) {
                next = arc->list;
                next->stat |= FILE_STATUS_OPERATING;
            }
            if (owner && (next->stat & FILE_STATUS_SYNC) != 0) {
                OS_WakeupThread_02002af8(next->queue);
                next = NULL;
            }
            func_0200494c(savedState);
        } else {
            if (owner) {
                if ((arc->flag & ARCHIVE_FLAG_RUNNING) != 0) {
                    FSFile idleFile;
                    func_0200b394(&idleFile);
                    idleFile.arc = arc;
                    arc->flag &= ~ARCHIVE_FLAG_RUNNING;
                    func_0200a2fc(&idleFile, COMMAND_IDLE);
                }
                if ((arc->flag & ARCHIVE_FLAG_SUSPENDING) != 0) {
                    arc->flag &= ~ARCHIVE_FLAG_SUSPENDING;
                    arc->flag |= ARCHIVE_FLAG_SUSPEND;
                    OS_WakeupThread_02002af8(arc->queue);
                }
            }
            func_0200494c(savedState);
        }
    }
    return next;
}
