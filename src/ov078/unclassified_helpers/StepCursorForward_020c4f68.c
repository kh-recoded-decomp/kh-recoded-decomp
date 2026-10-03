#include "nitro/types.h"

extern void PlaySoundEffect_0204d924(int bank, int id);
extern void InitSequence_020c471c(void *menu);

typedef struct {
    u8 pad[0x5d0];
    int cursor;
} MenuState;

void StepCursorForward_020c4f68(MenuState *menu)
{
    PlaySoundEffect_0204d924(0, 2);
    menu->cursor += 1;
    menu->cursor = menu->cursor % 5;
    InitSequence_020c471c(menu);
}
