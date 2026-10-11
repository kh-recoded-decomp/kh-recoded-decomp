#ifndef KH_RECODED_LIST_SLOT_TEMPLATE_H
#define KH_RECODED_LIST_SLOT_TEMPLATE_H

#include "nitro/types.h"

typedef struct ListSlotTemplate {
    s32 resourceId;
    s32 resourceParam;
    s32 x;
    s32 y;
    BOOL visible;
    BOOL raised;
} ListSlotTemplate;

typedef char ListSlotTemplateSizeCheck[(sizeof(ListSlotTemplate) == 0x18) ? 1 : -1];

extern ListSlotTemplate gPrimaryListSlotTemplates[12];
extern ListSlotTemplate gSecondaryListSlotTemplates[20];

#endif
