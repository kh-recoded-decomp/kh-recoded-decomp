#include "nitro/types.h"
#include "src/overlays/ov041/StageResources.h"

extern BOOL func_ov035_020bae94(void);
extern BOOL DrawStageItem(StageResourceItem *item);

static inline void DrawItem(StageResourceItem *item)
{
    if (item != NULL && (item->flags & STAGE_ITEM_DRAW) && !DrawStageItem(item)) {
        item->flags &= (u8)~STAGE_ITEM_DRAW;
    }
}

/* Draws every item marked for drawing; an item that turns out hidden is no longer drawn. */
void DrawStageItems(void)
{
    StageWork *work = gMovieContextState->stageWork;
    StageResourceGroup *group;
    int listIndex;
    StageResourceItem *item;
    int groupIndex;
    StageResourceList *list;
    int listItemIndex;
    int groupListIndex;
    StageResourceList *groupList;
    int itemIndex;

    if (!func_ov035_020bae94()) {
        return;
    }
    for (listIndex = 0; listIndex < 0x3e; listIndex++) {
        list = work->lists[listIndex];
        if (list != NULL) {
            for (listItemIndex = 0; listItemIndex < list->count; listItemIndex++) {
                item = &list->items[listItemIndex];
                DrawItem(item);
            }
        }
    }
    for (groupIndex = 0; groupIndex < 0x1b; groupIndex++) {
        group = work->groups[groupIndex];
        if (group != NULL) {
            for (groupListIndex = 0; groupListIndex < group->count; groupListIndex++) {
                groupList = &group->lists[groupListIndex];
                for (itemIndex = 0; itemIndex < groupList->count; itemIndex++) {
                    DrawItem(&groupList->items[itemIndex]);
                }
            }
        }
    }
}
