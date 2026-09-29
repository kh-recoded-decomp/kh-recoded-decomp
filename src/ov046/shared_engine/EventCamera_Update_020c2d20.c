#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    VecFx32 position;
    u8 pad_0C[0x1c];
} CameraView;

typedef struct EventCameraWork {
    u8 pad_00[0x120];
    s32 returnMode;
} EventCameraWork;

extern BOOL func_ov049_020c377c(EventCameraWork *work);
extern void func_ov046_020c2dd0(EventCameraWork *work, EventCameraWork *source, CameraView *view);
extern void func_ov046_020c1038(s32 mode, CameraView *view);

void *EventCamera_Update_020c2d20(EventCameraWork *work)
{
    CameraView view;

    if (func_ov049_020c377c(work)) {
        func_ov046_020c2dd0(work, work, &view);
        func_ov046_020c1038(work->returnMode, &view);
    }
    return NULL;
}
