#include "src/overlays/ov001/CounterHud.h"

extern void UpdateTimerHud(CounterHud *hud);
extern void UpdateAnimatedCounterHud(CounterHud *hud);
extern void DrawCounterHudParts(CounterHud *hud);
extern void RefreshCounterDigits(CounterHud *hud);
extern void UpdateCounterHudPanel(CounterHud *hud);
extern void RunLogoFadeSequence(CounterHud *hud);
extern void RunScoreTallySequence(CounterHud *hud);
extern void UpdateShortFadeSequence(CounterHud *hud);
extern void UpdateFadeSequence(CounterHud *hud);

CounterHandlers gCounterHudStateHandlers = {{
    NULL,
    UpdateTimerHud,
    UpdateAnimatedCounterHud,
    DrawCounterHudParts,
    RefreshCounterDigits,
    UpdateCounterHudPanel,
}};

FadeHandlers gFadeSequenceHandlers = {{
    NULL,
    RunLogoFadeSequence,
    RunScoreTallySequence,
    UpdateShortFadeSequence,
    UpdateFadeSequence,
}};
