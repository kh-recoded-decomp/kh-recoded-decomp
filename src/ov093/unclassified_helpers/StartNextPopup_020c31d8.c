#include "nitro/types.h"

typedef struct {
    int state;
    u32 flags;
    int frameCount;
} StateMachine;

typedef struct {
    int x;
    int y;
    u16 *text;
    int charBase;
} PopupRequest;

typedef struct {
    u8 pad_00[0x2c];
    StateMachine machine;
    int x;
    int y;
    int charBase;
    u8 pad_44[0x78 - 0x44];
    u16 *text;
    u8 pad_7c[0x8c - 0x7c];
    PopupRequest queue[30];
    int queueCount;
} PopupWork;

extern PopupWork *g_popupWork_020c50e4;
extern void StateMachine_SetState_020c3bc4(StateMachine *machine, int state);
extern void func_01ff878c(const void *src, void *dst, u32 size);

void StartNextPopup_020c31d8(void)
{
    PopupWork *work = g_popupWork_020c50e4;

    work->machine.flags = 0;
    work->x = work->queue[0].x - 0x80;
    work->y = work->queue[0].y - 0x60;
    work->charBase = work->queue[0].charBase;
    work->text = work->queue[0].text;
    StateMachine_SetState_020c3bc4(&work->machine, 2);
    func_01ff878c(&g_popupWork_020c50e4->queue[1], &g_popupWork_020c50e4->queue[0],
                  sizeof(g_popupWork_020c50e4->queue));
    g_popupWork_020c50e4->queueCount--;
}
