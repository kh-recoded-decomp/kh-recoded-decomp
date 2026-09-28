#include "nitro/types.h"

typedef struct Session {
    u8 pad_00[0x20];
    u32 flags;
    s32 activeHandle;
} Session;

extern BOOL func_ov001_02069160(s32 handle);
extern void func_ov001_0206922c(s32 handle);
extern void func_ov001_020690c8(void);
extern void func_ov001_02068e44(void);

void ReleaseSessionHandle_02062c98(Session *session, BOOL flush) {
    if (session->activeHandle != -1 && func_ov001_02069160(session->activeHandle) == 0) {
        func_ov001_0206922c(session->activeHandle);
    }
    if (flush) {
        func_ov001_020690c8();
        func_ov001_02068e44();
    }
    session->flags &= ~0x10;
    session->activeHandle = -1;
}
