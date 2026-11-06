/* Preserve the original wrapper's CodeWarrior integer types. */
#include "../include/nitro/types.h"

#include "nitro/types.h"

/* Native root input dispatch passes the focused widget word and key mask. */
extern void PlaySoundOnPanelEntryMatch(int selectedEntry, u32 buttonFlags);

extern unsigned int OnPanelSlot1Selected();
extern unsigned int OnPanelSlot16Selected();
extern unsigned int OnPanelSlot17Selected();
extern unsigned int gWirelessBoardGlobals;
extern unsigned int ResolveEntryStoreWord();
extern unsigned int SetWidgetRootInputCallback();

void InstallResultPanelCallbacks(void) {
  int work;

  work = gWirelessBoardGlobals;
  SetWidgetRootInputCallback((void *)(gWirelessBoardGlobals + 0x160),(u32)PlaySoundOnPanelEntryMatch);
  ResolveEntryStoreWord(work + 0x160,1,OnPanelSlot1Selected);
  ResolveEntryStoreWord(work + 0x160,0x10,OnPanelSlot16Selected);
  ResolveEntryStoreWord(work + 0x160,0x11,OnPanelSlot17Selected);
}
