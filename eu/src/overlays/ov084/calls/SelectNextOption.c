#include "nitro/types.h"

typedef struct SelectMenuCursor {
    u8 selection;
    u8 enabledOptions;
    u8 changed;
} SelectMenuCursor;

extern u16 data_02060500;
extern void PlaySoundEffect(int group, int soundId);

void SelectNextOption(SelectMenuCursor *cursor)
{
    do {
        cursor->selection++;
        if (cursor->selection >= 2) {
            if ((data_02060500 & 0x80) == 0) {
                cursor->selection = 1;
                return;
            }
            cursor->selection = 0;
        }
    } while ((1 << cursor->selection & cursor->enabledOptions) == 0);

    PlaySoundEffect(0, 0);
    cursor->changed = 1;
}
