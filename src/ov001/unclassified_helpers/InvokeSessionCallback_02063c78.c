#include "nitro/types.h"

typedef void (*SessionCallback)(void *argument);

typedef struct Session {
    u8 pad_0000[0x282c];
    SessionCallback callback;
} Session;

extern Session *data_ov001_020a0460;

void InvokeSessionCallback_02063c78(void *argument) {
    if (data_ov001_020a0460->callback != NULL) {
        data_ov001_020a0460->callback(argument);
    }
}
