#include "nitro/types.h"
#include "src/overlays/ov041/StageResources.h"

extern BOOL func_ov035_020bae94(void);
extern BOOL AdvanceStageItemAnimation(StageResourceItem *item, int delta);

static inline void ReleaseFinishedItem(StageResourceItem *item, int frame)
{
    if ((item->flags & STAGE_ITEM_VISIBLE) && !(item->flags & STAGE_ITEM_HELD) && AdvanceStageItemAnimation(item, frame) &&
        !(item->flags & STAGE_ITEM_PERSISTENT)) {
        item->flags &= (u8)~STAGE_ITEM_VISIBLE;
        item->flags &= (u8)~STAGE_ITEM_IN_USE;
    }
}

/* Each frame: hides and frees every shown item whose animation has finished (unless held or persistent). */
void ReleaseFinishedStageItems(int frame)
{
    StageWork *work = gMovieContextState->stageWork;
    int itemIndex;
    StageResourceGroup *group;
    StageResourceList *groupList;
    int listIndex;
    StageResourceList *list;
    int groupIndex;
    int groupListIndex;
    StageResourceItem *item;
    int listItemIndex;

    if (!func_ov035_020bae94()) {
        return;
    }
    for (listIndex = 0; listIndex < 0x3e; listIndex++) {
        list = work->lists[listIndex];
        if (list != NULL) {
            for (listItemIndex = 0; listItemIndex < list->count; listItemIndex++) {
                ReleaseFinishedItem(&list->items[listItemIndex], frame);
            }
        }
    }
    for (groupIndex = 0; groupIndex < 0x1b; groupIndex++) {
        group = work->groups[groupIndex];
        if (group != NULL) {
            for (groupListIndex = 0; groupListIndex < group->count; groupListIndex++) {
                groupList = &group->lists[groupListIndex];
                for (itemIndex = 0; itemIndex < groupList->count; itemIndex++) {
                    item = &groupList->items[itemIndex];
                    if (item != NULL) {
                        ReleaseFinishedItem(item, frame);
                    }
                }
            }
        }
    }
}
