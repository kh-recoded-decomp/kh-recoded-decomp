#include "nitro/types.h"

typedef struct {
    u16 startFrame;
    u16 endFrame;
} FrameTimer;

typedef struct {
    void *layer;
    u8 pad_04[0x10924 - 0x4];
    FrameTimer fadeTimer;
    FrameTimer scrollTimer;
    u8 pad_1092c;
    u8 state;
    u8 pad_1092e[0x10940 - 0x1092e];
} ScrollScreen;

typedef struct {
    u8 targets : 4;
    u8 command : 4;
    u8 pad_01[3];
    u16 duration;
    u8 pad_06[2];
    u8 param : 4;
    u8 pad_09[3];
    u32 value;
} ScrollTextCommand;

typedef struct {
    s32 waitFrames;
    s32 mode;
    u8 pad_08[0x14 - 0x8];
    ScrollScreen screens[2];
    u8 pad_21294[0x23ac1 - 0x21294];
    u8 rolling : 1;
    u8 pad_23ac2[2];
    int unk_bit0 : 1;
    int waitInput : 1;
    s32 skippable;
    u16 lineIndex;
    u16 lineCount;
    ScrollTextCommand *script;
    u8 pad_23ad4[0x30348 - 0x23ad4];
    FrameTimer lineTimer;
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals g_scrollText_020645a0;

extern BOOL FrameTimer_IsExpired_0206146c(FrameTimer *timer);
extern void FrameTimer_Start_020613e0(FrameTimer *timer, u16 duration);
extern void func_ov004_02063414(void *layer, int index, u32 value, ScrollTextCommand *command);
extern BOOL PrepareAndStartStream_0204dd4c(int streamIndex, int streamId);
extern void StopSoundStreamAtIndex_0204deb0(int handleIndex, int fadeFrame);

void RunScrollTextScript_020619a0(void)
{
    ScrollTextCommand *command;

    while (FrameTimer_IsExpired_0206146c(&g_scrollText_020645a0.work->lineTimer) &&
           g_scrollText_020645a0.work->lineIndex < g_scrollText_020645a0.work->lineCount) {
        command = &g_scrollText_020645a0.work->script[g_scrollText_020645a0.work->lineIndex];
        switch (command->command) {
        case 0:
            if (command->targets & 1) {
                FrameTimer_Start_020613e0(&g_scrollText_020645a0.work->screens[0].scrollTimer, command->duration);
            }
            if (command->targets & 2) {
                FrameTimer_Start_020613e0(&g_scrollText_020645a0.work->screens[1].scrollTimer, command->duration);
            }
            break;
        case 1:
            if (command->targets & 1) {
                FrameTimer_Start_020613e0(&g_scrollText_020645a0.work->screens[0].fadeTimer, command->duration);
            }
            if (command->targets & 2) {
                FrameTimer_Start_020613e0(&g_scrollText_020645a0.work->screens[1].fadeTimer, command->duration);
            }
            break;
        case 2:
            if (command->targets & 1) {
                FrameTimer_Start_020613e0(&g_scrollText_020645a0.work->screens[0].fadeTimer, command->duration);
            }
            if (command->targets & 2) {
                FrameTimer_Start_020613e0(&g_scrollText_020645a0.work->screens[1].fadeTimer, command->duration);
            }
            break;
        case 3: {
            ScrollTextWork *work = *(ScrollTextWork *volatile *)&g_scrollText_020645a0.work;
            FrameTimer_Start_020613e0(&work->screens[work->rolling ^ 1].fadeTimer, command->duration);
            break;
        }
        case 4:
            if (command->param == 1) {
                g_scrollText_020645a0.work->rolling ^= 1;
            }
            FrameTimer_Start_020613e0(&g_scrollText_020645a0.work->screens[g_scrollText_020645a0.work->rolling].fadeTimer, command->duration);
            break;
        case 5:
            FrameTimer_Start_020613e0(&g_scrollText_020645a0.work->lineTimer, command->duration);
            break;
        case 6:
        case 7:
            if (g_scrollText_020645a0.work->mode == 0) {
                g_scrollText_020645a0.work->rolling ^= 1;
            }
            if (command->targets & 1) {
                func_ov004_02063414(g_scrollText_020645a0.work->screens[0].layer, g_scrollText_020645a0.work->rolling ^ 1, command->value, command->command == 7 ? command : NULL);
            }
            if (command->targets & 2) {
                func_ov004_02063414(g_scrollText_020645a0.work->screens[1].layer, (g_scrollText_020645a0.work->rolling ^ 1) + 2, command->value, command->command == 7 ? command : NULL);
            }
            break;
        case 10:
            g_scrollText_020645a0.work->waitInput = 1;
            g_scrollText_020645a0.work->lineIndex++;
            return;
        case 8:
            if (command->param == 0) {
                PrepareAndStartStream_0204dd4c(0, 1);
            } else {
                StopSoundStreamAtIndex_0204deb0(0, command->duration);
            }
            break;
        case 9:
            break;
        }
        switch (command->command) {
        case 1:
        case 2:
            if (command->targets & 1) {
                g_scrollText_020645a0.work->screens[0].state = command->command;
            }
            if (command->targets & 2) {
                g_scrollText_020645a0.work->screens[1].state = command->command;
            }
            break;
        case 3:
        case 4:
            g_scrollText_020645a0.work->screens[0].state = command->command;
            g_scrollText_020645a0.work->screens[1].state = command->command;
            break;
        }
        g_scrollText_020645a0.work->lineIndex++;
    }
}


