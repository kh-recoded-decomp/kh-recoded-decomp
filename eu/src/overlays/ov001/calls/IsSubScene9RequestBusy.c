#include "nitro/types.h"

extern signed char *gSubScene9Work;

unsigned int IsSubScene9RequestBusy(void) {
  if ((*gSubScene9Work != '\0') && (*gSubScene9Work != '\x03')) {
    return 1;
  }
  return 0;
}
