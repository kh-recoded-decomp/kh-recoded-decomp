#include "nitro/types.h"

typedef struct {
    u8 pad[0x128];
    void *cells;
    int *firstSlots;
    int *secondSlots;
} ScoreScreen;

extern void SetDigitDisplay_020be2c8(void *cells, int first, int value, void *origin);
extern void SetEntrySlotsVisible_020b9580(void *cells, int *slots, u16 visible);

void SetScoreDisplay_020bf338(ScoreScreen *screen, int digitsA, int digitsB, int digitsC,
                              int valueC, u16 firstVisible, u16 secondVisible)
{
    SetDigitDisplay_020be2c8(screen->cells, digitsA, -1, NULL);
    SetDigitDisplay_020be2c8(screen->cells, digitsB, -1, NULL);
    SetDigitDisplay_020be2c8(screen->cells, digitsC, valueC, NULL);
    SetEntrySlotsVisible_020b9580(screen->cells, screen->firstSlots, firstVisible);
    SetEntrySlotsVisible_020b9580(screen->cells, screen->secondSlots, secondVisible);
}
