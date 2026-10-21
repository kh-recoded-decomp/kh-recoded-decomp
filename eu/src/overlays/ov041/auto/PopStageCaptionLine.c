#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

/* In state 0, takes the last laid-out line back off the caption layer; returns the lines left. */
int PopStageCaptionLine(StageCaption *caption)
{
    int count;
    int last;

    if (caption->state != 0) {
        return caption->unk50;
    }
    if (caption->unk50 == 0) {
        return 0;
    }
    count = caption->unk50 - 1;
    last = caption->lineCount - 1;
    caption->lineCount = last;
    caption->unk50 = count;
    caption->charOffset -= caption->lines[last].width * 8;
    return count;
}
