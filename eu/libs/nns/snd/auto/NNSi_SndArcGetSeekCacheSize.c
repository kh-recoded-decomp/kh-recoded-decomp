#include "libs/nns/snd/sndarc_seek_internal.h"

u32 NNSi_SndArcGetSeekCacheSize(void)
{
    return sCurrentSoundArchive->seekCacheSize;
}
