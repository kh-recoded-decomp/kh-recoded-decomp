#include "nitro/types.h"

typedef struct SessionPanel {
    u8 pad_000[0xc];
    u8 widget[0xa0];
    int counter;
    int active;
    char name[0x80];
    int pending;
} SessionPanel;

typedef struct Session {
    u8 pad_0000[0x2800];
    SessionPanel panel;
} Session;

extern Session *data_ov001_020a0460;
extern char data_ov001_0209e6d8[];
extern void func_ov022_020a787c(void *widget);
extern int OS_SPrintf_02002428(char *dst, const char *fmt, ...);

void ResetSessionPanel_02062b9c(void)
{
    SessionPanel *panel = &data_ov001_020a0460->panel;

    func_ov022_020a787c(panel->widget);
    panel->counter = 0;
    panel->active = 1;
    panel->pending = 0;
    OS_SPrintf_02002428(panel->name, data_ov001_0209e6d8);
}
