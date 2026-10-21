#include "nitro/types.h"

extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern BOOL PlaySoundChecked(int seqArcNo, int index);

void PlayStageSound(int seqArcNo, int index, BOOL checked)
{
    if (index != 0xff && index != -1) {
        if (checked) {
            PlaySoundChecked(seqArcNo, index);
        } else {
            PlaySoundEffect(seqArcNo, index);
        }
    }
}
