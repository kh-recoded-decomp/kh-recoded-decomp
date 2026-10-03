#include "nitro/types.h"

typedef struct CameraInputState {
    u32 unknown : 2;
    s32 skip : 1;
} CameraInputState;

typedef struct EventCameraWork {
    u8 pad_00[0x40];
    CameraInputState current;
    u8 pad_44[0x84];
    CameraInputState pending;
    u8 pad_cc[0xc0];
    void *activePath;
} EventCameraWork;

extern s32 func_ov046_020c0d68(void);
extern EventCameraWork *func_ov046_020c0d48(void);

BOOL CameraPath_ConsumeSkipRequest_020c2fd4(void)
{
    EventCameraWork *work;

    if (func_ov046_020c0d68() == 2) {
        work = func_ov046_020c0d48();
        if (work->activePath != NULL && work->current.skip) {
            work->pending.skip = 0;
            work->current.skip = work->pending.skip;
            return TRUE;
        }
    }
    return FALSE;
}
