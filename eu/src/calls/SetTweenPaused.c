/* Toggles pause mask 0x2 (bit 1) only when it changes; tickValue becomes now-tickValue on either transition. */
#define func_02003fd4 OS_GetTick
#define setStopwatchHeld_02052648 SetTweenPaused
#include "src/arm9/timing/setStopwatchHeld_02052648.c"
