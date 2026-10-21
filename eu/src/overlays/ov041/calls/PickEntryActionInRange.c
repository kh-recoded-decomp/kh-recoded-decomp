#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern const StageActionChoices gEmptyActionChoices;
extern int GetEntryNeededRange(StageEntry *entry);
extern u32 func_0202a9e4(u16 range);

/*
 * Picks one of an entry's actions that reach far enough, at random by their chances (out of 1000, less the
 * chances of the actions out of range); the last action is the fallback. -1 when none is in range.
 */
int PickEntryActionInRange(StageEntry *entry)
{
    int choiceCount;
    int count;
    StageActionChoices choices;
    int total;
    int i;
    StageEntryAction *action;
    int index;
    u16 chance;

    count = 0;
    choiceCount = 0;
    choices = gEmptyActionChoices;
    total = 1000;

    for (i = 0; i < entry->actionCount; i++) {
        action = &entry->actions[i];
        if (GetEntryNeededRange(entry) <= action->range) {
            choices.indices[count] = i;
            count++;
            choiceCount++;
        } else {
            total -= action->chance;
        }
    }
    for (i = 0; i < choiceCount; i++) {
        index = choices.indices[i];
        chance = entry->actions[index].chance;
        if (func_0202a9e4(total) < chance || index == entry->actionCount - 1) {
            return index;
        }
        total -= chance;
    }
    return -1;
}
