#include "nitro/types.h"

typedef struct BoardState {
    char pad0000[0x64f0];
    void *listener;
    char pad64f4[4];
    int needsText;
    char pad64fc[0x66e0 - 0x64fc];
    int useChannel;
    char pad66e4[0x66fe - 0x66e4];
    s8 cursor;
} BoardState;

typedef void (*BoardCallback)(void);

extern BoardState *data_ov024_020b7520;
extern char data_ov024_020b74fc[];
extern void func_ov024_020b6df4(void);
extern void func_ov024_020b5800(void);
extern void func_ov024_020b664c(void);
extern void func_ov024_020b6bb0(void);
extern void func_0200110c(int channel, void *target, BoardCallback callback, int arg);
extern void *func_ov001_0207157c(BoardCallback callback);

BoardCallback StartBoardScreen_020b6b40(void)
{
    BoardCallback next = NULL;

    if (data_ov024_020b7520->needsText) {
        next = func_ov024_020b6df4;
        func_ov024_020b664c();
        data_ov024_020b7520->cursor = -1;
        func_ov024_020b6bb0();
    }
    if (data_ov024_020b7520->useChannel) {
        func_0200110c(1, data_ov024_020b74fc, func_ov024_020b5800, 0);
    } else {
        data_ov024_020b7520->listener = func_ov001_0207157c(func_ov024_020b5800);
    }
    return next;
}
