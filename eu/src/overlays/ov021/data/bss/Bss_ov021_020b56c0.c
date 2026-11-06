#include "nitro/types.h"

/* Symbol discovery keeps the typed view at the backing storage address.
 * This conditional view is not a second allocation in the native C build. */
#if defined(LINKER_SYMBOL_SCAN)
static u32 gActiveFieldContext[3];
#endif

static u32 gActiveFieldContextStorage[3];
static u32 gActiveSubModeState;
