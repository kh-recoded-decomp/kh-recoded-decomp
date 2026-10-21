#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern BOOL DestroyFndObjectList(void *list);
extern void FreePointerIfSet(void **pointer);

/* Takes the caption down and frees its message file. */
void DestroyStageCaption(StageCaption *caption)
{
    DestroyFndObjectList(caption);
    FreePointerIfSet(&caption->messages);
}
