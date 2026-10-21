#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern StageHudEntry *GetHudEntry(int id);
extern int GetItemMenuIcon(int itemId);
extern void func_ov041_020ce40c(StageCaption *caption, StageTextLine *line, u32 messageId, int rows, int columns,
                                BOOL fixedStart);
extern void DrawStageCaptionLine(StageCaption *caption, StageTextLine *line, int arg);
extern void UploadStageCaptionLayer(StageCaption *caption);
extern StageCaptionTriple gStageCaptionTriples[21];

/* Shows the three requested lines as one combined entry when their items' menu icons form a known triple. */
BOOL CombineStageCaptionTriple(StageCaption *caption)
{
    BOOL found = FALSE;
    StageHudEntry *entries[3];
    int i;
    StageCaptionTriple *triple;

    if (caption->unk50 < 3) {
        return FALSE;
    }
    for (i = 0; i < 3; i++) {
        entries[i] = GetHudEntry(caption->lines[i].messageId);
    }
    for (i = 0; i < sizeof(gStageCaptionTriples) / sizeof(gStageCaptionTriples[0]); i++) {
        triple = &gStageCaptionTriples[i];
        if (triple->first == GetItemMenuIcon(entries[0]->messageId) &&
            triple->second == GetItemMenuIcon(entries[1]->messageId) &&
            triple->third == GetItemMenuIcon(entries[2]->messageId)) {
            func_ov041_020ce40c(caption, &caption->queued[0], triple->combined,
                                (u32)(entries[0]->rows + entries[1]->rows + entries[2]->rows + 1) / 2, 3, FALSE);
            DrawStageCaptionLine(caption, &caption->queued[0], 2);
            UploadStageCaptionLayer(caption);
            caption->queuedCount = 1;
            found = TRUE;
            break;
        }
    }
    return found;
}
