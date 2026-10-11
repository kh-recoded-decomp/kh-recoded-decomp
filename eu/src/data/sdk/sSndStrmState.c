#include "nnsys/snd.h"

typedef char StreamListMustBe12Bytes[sizeof(NNSFndList) == 12 ? 1 : -1];

/* Global stream registry and the current block passed to each user callback.
 * Buffer slots are indexed by the stream's channel list, not hardware IDs. */
BOOL sSndStrmInitialized;
NNSFndList sSndStrmList;
void *sStrmCallbackBuffers[16];
