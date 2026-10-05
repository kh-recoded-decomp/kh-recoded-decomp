#include "nitro/types.h"

typedef struct CounterPanel {
    u8 current;
    u8 total;
    u8 pad_02[0xa];
    u32 timerStart;
    u8 pad_10[8];
    u32 startTick;
    u8 pad_1c[4];
    u16 history[2];
    u16 state;
    u16 pending : 14;
    u16 pendingHigh : 2;
    u32 flags;
    u32 historyIndex;
    u8 pad_30[0x10];
    u32 finishGraphics;
    u32 stepGraphics;
} CounterPanel;

extern char data_ov001_0209dfc8[];
extern void func_ov001_0207123c(void);
extern u16 RefreshCounterRecordPositions_0207d790(CounterPanel *panel);
extern u16 func_ov001_0207d838(u32 value);
extern void func_ov001_0207d800(CounterPanel *panel, u32 graphics);
extern void ShowTwoDigitCounters_0207d984(CounterPanel *panel);
extern void GFXi_EnqueueCommand_02014090(u32 a, u32 b, u32 c, u32 d);
extern u32 func_0202a7a4(void);

BOOL AdvanceCounterPanel_0207da58(CounterPanel *panel)
{
    BOOL finished;
    u32 value;

    func_ov001_0207123c();
    finished = FALSE;
    if (panel->current < panel->total) {
        panel->current++;
    }
    value = panel->pending;
    if (value >= 1 && value <= 3) {
        value = RefreshCounterRecordPositions_0207d790(panel);
    }
    panel->history[panel->historyIndex] = func_ov001_0207d838(value);
    panel->historyIndex ^= 1;
    GFXi_EnqueueCommand_02014090(0xf, 0x1c2, (u32)data_ov001_0209dfc8, 0xe);
    panel->state = 1;
    panel->pending = 0;
    panel->flags &= ~2;
    if (panel->current == panel->total) {
        func_ov001_0207d800(panel, panel->finishGraphics);
        panel->timerStart = 0;
        panel->startTick = func_0202a7a4();
        finished = TRUE;
    } else {
        func_ov001_0207d800(panel, panel->stepGraphics);
    }
    ShowTwoDigitCounters_0207d984(panel);
    return finished;
}
