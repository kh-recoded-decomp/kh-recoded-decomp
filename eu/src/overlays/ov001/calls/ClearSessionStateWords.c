#include "nitro/types.h"

/* Only the three reset words are identified; their state meanings remain unknown.
 * Session +0x2740 is a native view base, followed by 0x68 bytes of opaque data. */

typedef struct SessionStateWordsView {
    u8 pad_00[0x68];
    int values[3];
} SessionStateWordsView;

typedef struct SessionStateOwnerView {
    u8 pad_0000[0x2740];
    SessionStateWordsView stateWords;
} SessionStateOwnerView;

extern SessionStateOwnerView *data_ov001_020a0480;

void ClearSessionStateWords(void)
{
    SessionStateWordsView *stateWords = &data_ov001_020a0480->stateWords;
    int i;

    for (i = 0; i < 3; i++) {
        stateWords->values[i] = 0;
    }
}
