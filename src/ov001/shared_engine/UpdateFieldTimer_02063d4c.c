#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x214];
    u32 lowBits : 3;
    u32 timerLocked : 1;
    u32 highBits : 28;
    u8 pad_0218[0x29b0 - 0x218];
    s32 timeLimit;
    u8 visible : 1;
    u8 running : 1;
    u8 countUp : 1;
    u8 restBits : 5;
} FieldGlobal;

extern FieldGlobal *data_ov001_020a0460;

extern BOOL func_ov001_020645c8(int bitOffset);
extern void func_ov001_020645dc(int bitOffset);
extern void func_ov001_020645e8(int bitOffset);
extern void WriteSessionPackedBits_0206459c(int bitOffset, int bitCount, u32 value);
extern void StartCountdownTimer_0207d134(int slot, BOOL countDown);
extern void StartPanelScrollOut_0207d28c(int slot);
extern void func_ov001_02068d8c(int slot);
extern void func_ov001_02068e08(int slot);
extern void func_ov001_02068e34(int slot);
extern int func_ov001_02068ea4(int slot);
extern void func_ov001_02068ed0(int value, int slot);
extern void func_ov001_02068ef0(int value);
extern void func_ov001_0207d384(BOOL enable);
extern void func_ov001_0207d3a4(int seconds);
extern int GetClampedTimerValue_02063f90(void);

void UpdateFieldTimer_02063d4c(int command, int value)
{
    FieldGlobal *global = data_ov001_020a0460;
    BOOL flag;
    int current;
    int elapsed;
    int delta;

    switch (command) {
    case 0:
        if (!func_ov001_020645c8(0x35f0)) {
            flag = TRUE;
            if (value & 1) {
                flag = FALSE;
            }
            global->countUp = (u8)flag;
            if (!(value & 2)) {
                /* Pointer arms keep the original branch layout */
                StartCountdownTimer_0207d134(0, (s32)(global->countUp ? NULL : (void *)1));
            } else {
                StartPanelScrollOut_0207d28c(0);
            }
            func_ov001_02068d8c(0);
            func_ov001_02068e08(0);
            func_ov001_020645dc(0x35f0);
            WriteSessionPackedBits_0206459c(0x35f1, 2, value & 3);
            global->visible = 1;
        }
        break;
    case 1:
        if (!global->timerLocked && !func_ov001_020645c8(0x1a05)) {
            global->timeLimit = value * 1000;
            func_ov001_02068ed0(global->countUp ? 0 : global->timeLimit, 0);
            global->running = 0;
        }
        break;
    case 2:
        func_ov001_0207d384(TRUE);
        func_ov001_02068e34(0);
        func_ov001_020645dc(0x35f3);
        break;
    case 3:
        if (value != 0) {
            func_ov001_02068e08(0);
            func_ov001_020645dc(0x35f4);
        } else {
            func_ov001_02068e34(0);
            func_ov001_020645e8(0x35f4);
        }
        break;
    case 4:
        if (value != 0) {
            flag = TRUE;
        } else {
            flag = FALSE;
        }
        if (global->visible) {
            func_ov001_0207d384(flag);
        }
        WriteSessionPackedBits_0206459c(0x35f3, 1, flag & 1);
        break;
    case 5:
        if (GetClampedTimerValue_02063f90()) {
            delta = value;
            current = func_ov001_02068ea4(0);
            if (global->countUp) {
                elapsed = global->timeLimit - current;
                if (elapsed + value > 0x923d8) {
                    delta = 0x923d8 - elapsed;
                }
                current -= delta;
            } else {
                if (current + value > 300000) {
                    delta = 300000 - current;
                }
                current += delta;
            }
            func_ov001_02068ed0(current, 0);
            func_ov001_0207d3a4((s16)(value / 1000));
            if (func_ov001_020645c8(0x35f0)) {
                WriteSessionPackedBits_0206459c(0x35e6, 10, (u32)GetClampedTimerValue_02063f90() / 1000);
            }
        }
        break;
    case 6:
        func_ov001_02068ef0((s16)value);
        break;
    case 7:
        if (func_ov001_020645c8(0x35f0)) {
            WriteSessionPackedBits_0206459c(0x35f1, 2, 0);
            WriteSessionPackedBits_0206459c(0x35e6, 10, 0);
            func_ov001_020645e8(0x35f3);
            func_ov001_020645e8(0x35f4);
            func_ov001_020645e8(0x35f0);
            global->running = 0;
            global->countUp = 0;
            global->timeLimit = 0;
            func_ov001_02068e08(0);
            func_ov001_0207d384(FALSE);
        }
        break;
    }
}
