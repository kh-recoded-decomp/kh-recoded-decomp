/* Behavior: Toggles a stopwatch between running and held states while preserving elapsed ticks.
 * Inputs/outputs and evidence: On a state transition, subtracts the stored tick value from the current hardware tick count and updates the held bit.
 * Uncertainty: The structure's unrelated fields are unknown; elapsed-tick interpretation follows both subtraction branches.
 * Source: khdays-decomp/src/calls/func_02036104.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
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
