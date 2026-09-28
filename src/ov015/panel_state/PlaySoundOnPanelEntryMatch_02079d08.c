#include "nitro/types.h"

extern int data_ov015_020812e0;
extern int func_ov027_020b90a4(int panel, int value);
extern void func_0204d924(int soundId, int arg);

/* Plays a sound when the selected panel entry matches. */
void PlaySoundOnPanelEntryMatch_02079d08(int selectedEntry, u32 buttonFlags) {
    int entry;

    entry = func_ov027_020b90a4(data_ov015_020812e0 + 0x160, 0x10);
    if ((entry != selectedEntry) &&
        (entry = func_ov027_020b90a4(data_ov015_020812e0 + 0x160, 0x11), entry != selectedEntry)) {
        return;
    }
    if (((buttonFlags & 0x20) == 0) && ((buttonFlags & 0x10) == 0)) {
        return;
    }
    func_0204d924(2, 0);
}
