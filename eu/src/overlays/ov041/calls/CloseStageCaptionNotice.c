#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern void (*gStageCaptionStates[])(StageCaption *caption);
extern void SetStageCaptionState(StageCaption *caption, int state);
extern void CallVirtualHandlerSlot1(void *object, int arg);
extern void DrawStageCaptionLine(StageCaption *caption, StageTextLine *line, int style);
extern void Text_UploadTileBuffer(void *layer);

/* Takes a notice down: goes back to the state before it and lays that state's lines out again. */
void CloseStageCaptionNotice(StageCaption *caption)
{
    int i;
    int count;
    StageTextLine *lines;
    int style;

    if (caption->state != 3) {
        return;
    }
    SetStageCaptionState(caption, caption->previousState);
    switch (caption->state) {
    case 0:
        lines = caption->lines;
        count = caption->unk50;
        style = 1;
        break;
    case 1:
        count = 1;
        caption->lineCount = count;
        lines = &caption->line;
        style = 0;
        break;
    case 2:
        lines = caption->queued;
        count = caption->queuedCount;
        style = 2;
        break;
    default:
        count = 0;
        break;
    }
    caption->charOffset = 0;
    CallVirtualHandlerSlot1(caption, 0);
    for (i = 0; i < count; i++) {
        DrawStageCaptionLine(caption, &lines[i], style);
        caption->charOffset += lines[i].width * 8;
    }
    Text_UploadTileBuffer(caption);
    gStageCaptionStates[caption->state](caption);
}
