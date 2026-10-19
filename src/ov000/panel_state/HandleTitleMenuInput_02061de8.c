#include "nitro/types.h"

typedef struct TitleMenu {
    u8 unknown0000[0x50];
    int selected;
    u8 unknown0054[0x66d0 - 0x54];
    u64 lastNavigationTick;
} TitleMenu;

extern u16 data_02060500;
extern u32 gTitleMenuActionCodes[4];
extern BOOL IsPanelFlagSet(TitleMenu *menu, int index);
extern BOOL PlaySoundEffect(int channel, int sound);
extern u64 OS_GetTick(void);
extern void SetPanelState(TitleMenu *menu, int state, int duration, int delay);
extern BOOL PrepareAndStartStream(int index, int stream);
extern void StopSoundStreamAtIndex(int index, int duration);

/* Returns the selected action on confirmation, or -1 while navigating.
 * Disabled entries are skipped, wrapping around the four menu choices. */
int HandleTitleMenuInput_02061de8(TitleMenu *menu, u32 repeatKeys)
{
    int candidate = 0;
    int result = -1;
    int step;

    if (repeatKeys & 0x40) {
        for (step = 1; step < 4; step++) {
            candidate = (menu->selected + 4 - step) % 4;
            if (IsPanelFlagSet(menu, candidate)) {
                menu->selected = candidate;
                PlaySoundEffect(0, 0);
                break;
            }
        }
        menu->lastNavigationTick = OS_GetTick();
    } else if (repeatKeys & 0x80) {
        for (step = 1; step < 4; step++) {
            candidate = (menu->selected + step) % 4;
            if (IsPanelFlagSet(menu, candidate)) {
                menu->selected = candidate;
                PlaySoundEffect(0, 0);
                break;
            }
        }
        menu->lastNavigationTick = OS_GetTick();
    } else if (data_02060500 & 9) {
        switch (menu->selected) {
        case 0: {
            int duration = 30;
            SetPanelState(menu, 0, duration, duration);
            PrepareAndStartStream(1, 3);
            StopSoundStreamAtIndex(0, duration);
            break;
        }
        case 1:
        case 2:
            SetPanelState(menu, 1, 16, 0);
            PlaySoundEffect(0, 1);
            break;
        case 3:
            SetPanelState(menu, 1, 16, 0);
            PlaySoundEffect(0, 1);
            break;
        }
        result = gTitleMenuActionCodes[menu->selected];
    }
    return result;
}
