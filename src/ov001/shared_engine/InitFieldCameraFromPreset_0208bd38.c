#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 heading;
    u8 pad_04[8];
    fx32 nearClip;
    fx32 farClip;
    VecFx32 position;
    VecFx32 target;
    u8 pad_2c[0xc];
} CameraView;

typedef struct {
    CameraView view;
    s32 pitch;
    fx32 distance;
    u8 pad_40[8];
} CameraPreset;

typedef struct {
    CameraView view;
    VecFx32 anchor;
    s32 pitch;
    s32 elevation;
    s32 roll;
    u8 pad_50[0x30];
    fx32 distance;
    s32 headingAngle;
    u8 pad_88[8];
    s32 followMode;
    u8 pad_94[4];
    s32 followTargetA;
    s32 followTargetB;
    u8 pad_a0[0x134];
    void *message;
    void *loader;
    u16 loading;
    u8 pad_1de[2];
    s32 pendingId;
} FieldCamera;

extern FieldCamera *data_ov001_020a04f4;
extern char data_ov001_0209f318[];
extern BOOL func_ov001_02088960(void);
extern void func_ov021_020af634(CameraPreset *preset);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern int Math_AsinIdx_0202aaa8(fx32 value);
extern void ResetFieldCamera_0208ae68(void);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern void func_0202a5ac(void *loader, void *callback);
extern void func_ov001_0208b780(void);

void InitFieldCameraFromPreset_0208bd38(void)
{
    FieldCamera *camera = data_ov001_020a04f4;
    CameraPreset preset;
    fx32 slope;

    if (func_ov001_02088960()) {
        func_ov021_020af634(&preset);
        camera->view = preset.view;
        camera->pitch = preset.pitch;
        camera->distance = preset.distance;
        if (camera->pitch >= 0x7ff8) {
            camera->pitch -= 0xfff0;
        }
        camera->anchor = camera->view.position;
        slope = FX_Div_01ff9c84(camera->view.target.y - camera->view.position.y, camera->distance);
        if (slope >= -0x1000 && slope <= 0x1000) {
            camera->elevation = -(u16)Math_AsinIdx_0202aaa8(slope);
        }
        camera->roll = 0;
        camera->headingAngle = Math_AsinIdx_0202aaa8(camera->view.heading);
        camera->followTargetB = -1;
        camera->followTargetA = -1;
        camera->followMode = 0;
    } else {
        ResetFieldCamera_0208ae68();
    }
    camera->pendingId = -1;
    camera->message = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov001_0209f318, 0xd, FALSE);
    camera->loading = 1;
    func_0202a5ac(camera->loader, func_ov001_0208b780);
}

