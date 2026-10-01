#include "nitro/types.h"

typedef struct MessageWindow {
    u8 pad_00[8];
    int state;
    u8 pad_0c[0x58];
    int hasMorePages;
    u8 pad_68[0x1c];
    u32 waitTickLow;
    u32 waitTickHigh;
} MessageWindow;

extern int *data_ov001_020a04c4;
extern void *GetSceneTagTracker_020711b0(void);
extern void PlaceWindowCornerTag_02079578(MessageWindow *window);
extern void func_ov001_02079790(MessageWindow *window, u32 flag);
extern u64 func_02003fd4(void);

void FinishMessageWindowPage_02079f2c(MessageWindow *window)
{
    int *mode = data_ov001_020a04c4;
    u64 tick;

    GetSceneTagTracker_020711b0();
    if (window->hasMorePages == 0) {
        if (*mode != 1) {
            PlaceWindowCornerTag_02079578(window);
        }
        window->state = 6;
        return;
    }
    func_ov001_02079790(window, 0);
    window->state = 5;
    tick = func_02003fd4();
    window->waitTickLow = tick;
    window->waitTickHigh = tick >> 32;
}
