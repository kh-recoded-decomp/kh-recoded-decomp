#include "nitro/types.h"

extern unsigned int *gFieldSceneEntryContext;
extern unsigned int HighlightSelectedMenuPanels();

u8 SetMenuItemKind(int index,u8 value,int refresh) {
  u8 previous;
  u8 *entry;

  entry = *(u8 **)(*gFieldSceneEntryContext + index * 4 + 8);
  previous = *entry;
  *entry = value;
  if (refresh != 0) {
    HighlightSelectedMenuPanels();
  }
  return previous;
}
