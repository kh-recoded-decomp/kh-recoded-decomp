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

extern s32 Camera_GetModeValue(void);
extern EventCameraWork *Camera_GetEventWork(void);

BOOL CameraPath_ConsumeSkipRequest(void)
{
    EventCameraWork *work;

    if (Camera_GetModeValue() == 2) {
        work = Camera_GetEventWork();
        if (work->activePath != NULL && work->current.skip) {
            work->pending.skip = 0;
            work->current.skip = work->pending.skip;
            return TRUE;
        }
    }
    return FALSE;
}
