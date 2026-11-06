#include "nitro/types.h"

extern signed char *gSubScene9Work;

unsigned int func_ov001_02066e70(void) {
  if ((*gSubScene9Work != '\0') && (*gSubScene9Work != '\x03')) {
    return 1;
  }
  return 0;
}
