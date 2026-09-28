typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct {
    u32 field_00;
    u32 field_04;
    u32 field_08;
    u32 field_0c;
    u64 tickValue;
    u32 field_18_bit0 : 1;
    u32 isHeld : 1;
    u32 field_18_rest : 30;
} Stopwatch;

extern u64 func_02003fd4(void);

void setStopwatchHeld_02052648(Stopwatch *stopwatch, int hold)
{
    if (hold != 0) {
        if (stopwatch->isHeld != 0) {
            return;
        }
        stopwatch->isHeld = 1;
        stopwatch->tickValue = func_02003fd4() - stopwatch->tickValue;
    } else {
        if (stopwatch->isHeld == 0) {
            return;
        }
        stopwatch->isHeld = 0;
        stopwatch->tickValue = func_02003fd4() - stopwatch->tickValue;
    }
}
