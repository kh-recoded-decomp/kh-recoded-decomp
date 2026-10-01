#include "nitro/types.h"

typedef struct SceneRequest {
    char name[0x10];
    u32 param;
} SceneRequest;

typedef struct Session {
    u8 pad_0000[0x20];
    u32 flags;
    u8 pad_0024[0x2808 - 0x24];
    s8 mode;
} Session;

extern Session *data_ov001_020a0460;
extern void func_ov001_02066810(void);
extern void NotifyManagerEntryObjects_0206e4b4(void);
extern void func_ov001_0206e444(s32 enable);
extern void func_ov021_020af7e4(s32 value);
extern void func_ov001_0208780c(void);
extern void func_ov001_020877c4(void);
extern void *OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void ActorManager_StartScene_02088974(SceneRequest *request);

void StartSessionScene_020636f8(const char *sceneName) {
    SceneRequest request;
    if (data_ov001_020a0460->mode == 3 || data_ov001_020a0460->mode == 7) {
        request.param = 0;
    } else {
        request.param = 1;
    }
    func_ov001_02066810();
    NotifyManagerEntryObjects_0206e4b4();
    func_ov001_0206e444(1);
    func_ov021_020af7e4(1);
    func_ov001_0208780c();
    func_ov001_020877c4();
    OS_SPrintf_02002428(request.name, sceneName);
    ActorManager_StartScene_02088974(&request);
    data_ov001_020a0460->flags |= 0x20;
}
