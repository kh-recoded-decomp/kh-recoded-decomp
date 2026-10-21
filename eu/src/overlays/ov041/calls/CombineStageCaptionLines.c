#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern StageHudEntry *GetHudEntry(int id);
extern void SetStageCaptionLine(StageCaption *caption, StageTextLine *line, u32 messageId, int rows, int columns,
                                BOOL fixedStart);
extern void DrawStageCaptionLine(StageCaption *caption, StageTextLine *line, int arg);
extern StageCaptionCombo gStageCaptionPairs[64];

/* Shows lines index and index + 1 as one combined entry when their HUD entries form a known pair (only checks
 * whether they do when checkOnly is set). */
BOOL CombineStageCaptionLines(StageCaption *caption, int index, BOOL checkOnly)
{
    BOOL found = FALSE;
    StageHudEntry *entries[2];
    int i;
    StageCaptionCombo *combo;

    for (i = 0; i < 2; i++) {
        entries[i] = GetHudEntry(caption->lines[index + i].messageId);
    }
    for (i = 0; i < sizeof(gStageCaptionPairs) / sizeof(gStageCaptionPairs[0]); i++) {
        combo = &gStageCaptionPairs[i];
        if (entries[0]->messageId == combo->first && entries[1]->messageId == combo->second) {
            if (!checkOnly) {
                SetStageCaptionLine(caption, &caption->queued[index], combo->combined,
                                    entries[0]->rows + entries[1]->rows, 2, FALSE);
                DrawStageCaptionLine(caption, &caption->queued[index], 2);
            }
            found = TRUE;
            break;
        }
    }
    return found;
}
