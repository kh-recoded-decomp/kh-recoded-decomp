#include "nitro/types.h"

typedef struct {
    u32 words[14];
} CameraCutHeader;

typedef struct {
    CameraCutHeader header;
    s32 target;
    s32 focus;
    u8 pad_40[0x8];
} CameraCutParams;

typedef struct {
    CameraCutHeader header;
    u8 pad_38[0x44 - 0x38];
    s32 defaultTarget;
    u8 pad_48[0x80 - 0x48];
    s32 focus;
    u8 pad_84[0x98 - 0x84];
    s32 cutId;
    u8 pad_9c[0x1d4 - 0x9c];
    void *buffer;
    u32 task;
    u16 active;
    u8 pad_1de[0x1e0 - 0x1de];
    s32 targetOverride;
} EventCameraManager;

extern EventCameraManager *data_ov001_020a04f4;

extern int ZeroHalfThenFree_0202cd78(void *block);
extern u32 func_ov001_02088960(void);
extern void func_ov021_020af694(CameraCutParams *params);
extern BOOL func_02028940(void);
extern void func_ov021_020af6c4(void);
extern void SetSubModeFrozen_020af434(BOOL frozen);
extern void func_ov021_020af508(int value);
extern void func_ov001_0208ae68(void);
extern void func_0202a5ac(u32 task, void (*callback)(void));
extern void func_ov001_0208b77c(void);

void FinishEventCameraCut_0208be1c(void) {
    EventCameraManager *manager = data_ov001_020a04f4;
    CameraCutParams params;

    if (manager->active == 0) {
        return;
    }
    if (manager->buffer != NULL) {
        ZeroHalfThenFree_0202cd78(manager->buffer);
        manager->buffer = NULL;
    }
    if (func_ov001_02088960()) {
        if (manager->cutId != -1) {
            params.header = manager->header;
            if (manager->targetOverride != -1) {
                params.target = manager->targetOverride;
            } else {
                params.target = manager->defaultTarget;
            }
            params.focus = manager->focus;
            func_ov021_020af694(&params);
        }
        if (func_02028940()) {
            func_ov021_020af6c4();
            SetSubModeFrozen_020af434(FALSE);
            func_ov021_020af508(0);
        }
    }
    func_ov001_0208ae68();
    manager->active = 0;
    func_0202a5ac(manager->task, func_ov001_0208b77c);
}
