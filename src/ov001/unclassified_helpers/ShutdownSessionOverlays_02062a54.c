#include "nitro/types.h"

typedef struct SubOverlayWork {
    u8 pad_00[0x10];
    BOOL (*poll)(void);
    void (*shutdown)(void);
    u8 pad_18[0x18];
} SubOverlayWork;

typedef struct SubOverlaySlot {
    s32 activeId;
    s32 overlayId;
    s8 state;
    u8 pad_09[3];
    SubOverlayWork work;
} SubOverlaySlot;

typedef struct Session {
    u8 pad_0000[0x14];
    s32 overlayId;
    u8 pad_0018;
    s8 overlayState;
    u8 pad_001a[0x2800 - 0x1a];
    SubOverlaySlot subOverlay;
} Session;

extern Session *data_ov001_020a0460;
extern void func_ov001_020633d4(void);
extern void func_02029f98(int processor, int overlayId);
extern void func_01ff86fc(u32 value, void *destination, u32 size);
extern void func_02035774(void);
extern void func_0203574c(void);
extern void func_ov001_020674a0(void);

s32 ShutdownSessionOverlays_02062a54(void) {
    Session *session = data_ov001_020a0460;
    SubOverlaySlot *slot = &session->subOverlay;

    if (session->subOverlay.state != 1) {
        func_ov001_020633d4();
    }
    if (slot->activeId != -1) {
        slot->work.shutdown();
        if (slot->overlayId != -1) {
            func_02029f98(0, slot->overlayId);
        }
        func_01ff86fc(0, &slot->work, sizeof(SubOverlayWork));
        slot->activeId = -1;
    }
    if (session->overlayId != -1) {
        func_02029f98(0, session->overlayId);
        session->overlayId = -1;
        session->overlayState = -1;
    }
    func_02035774();
    func_0203574c();
    func_ov001_020674a0();
    return 1;
}
