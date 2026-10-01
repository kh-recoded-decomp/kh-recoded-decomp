#include "nitro/types.h"

struct FSArchive;

typedef struct FSFile {
    struct FSFile *next;
    void *userdata;
    struct FSArchive *arc;
    u32 stat;
    void *argument;
    int error;
} FSFile;

typedef struct FSArchive {
    u32 name;
    struct FSArchive *next;
    FSFile *list;
    u8 queue[8];
    u32 flag;
} FSArchive;

extern void RunResetCallbackAndIdle_02004cf0(void);
extern u32 func_02004938(void);
extern void func_0200494c(u32 state);
extern void func_0200a200(FSFile *file, u32 result);
extern FSFile *FSi_NextCommand_0200a67c(FSArchive *arc, BOOL owner);
extern void AdvanceCommandQueue_0200a8ac(FSFile *file);
extern void func_0200a828(FSFile *file);

static inline BOOL FS_IsBusy(const FSFile *file)
{
    return (file->stat & 1) ? TRUE : FALSE;
}

BOOL FSi_SendCommand_0200a930(FSFile *file, u32 command, BOOL blocking)
{
    FSArchive *arc;
    u32 state;
    BOOL owner = FALSE;
    BOOL result = owner;
    BOOL busy;

    arc = file->arc;
    busy = FS_IsBusy(file);

    if (busy != FALSE) {
        RunResetCallbackAndIdle_02004cf0();
    }
    if (arc == NULL) {
        file->error = 6;
        return FALSE;
    }
    file->error = 2;
    file->stat = (file->stat & ~0xff00) | (command << 8) | 1;
    file->next = NULL;
    if (blocking) {
        file->stat |= 4;
    }
    state = func_02004938();
    if (arc->flag & 0x80) {
        func_0200a200(file, 3);
    } else {
        FSFile **link = &arc->list;
        while (*link != NULL) {
            link = &(*link)->next;
        }
        *link = file;
    }
    owner = FALSE;
    if (arc->list == file && (arc->flag & 0x10) == 0) {
        owner = TRUE;
    }
    func_0200494c(state);
    if (file->error != 3) {
        FSFile *next = FSi_NextCommand_0200a67c(arc, owner);
        if (blocking) {
            AdvanceCommandQueue_0200a8ac(file);
            result = (file->error == 0);
        } else {
            if (next != NULL) {
                func_0200a828(next);
            }
            result = TRUE;
        }
    }
    return result;
}
