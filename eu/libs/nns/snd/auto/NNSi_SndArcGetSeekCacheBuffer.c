#include "libs/nns/snd/sndarc_seek_internal.h"

void *NNSi_SndArcGetSeekCacheBuffer(void)
{
    return sCurrentSoundArchive->seekCacheBuffer;
}
