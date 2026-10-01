#include "nitro/types.h"

typedef struct {
    s16 kind;
    s16 number;
} SessionName;

typedef struct {
    u8 pad[0x208];
    SessionName name;
} Session;

extern Session *data_ov001_020a0460;
extern const char data_ov001_0209e6f0[];
extern const char data_ov001_0209e6f4[];
extern void *OS_SPrintf_02002428(char *dst, const char *fmt, ...);

void FormatSessionNumber_02063578(int number, char *buffer) {
    SessionName *name = &data_ov001_020a0460->name;
    if (number != 0) {
        OS_SPrintf_02002428(buffer, data_ov001_0209e6f0, number, name);
        return;
    }
    OS_SPrintf_02002428(buffer, data_ov001_0209e6f4, name->number, name);
}
