#ifndef KH_RECODED_OV093_POPUP_DEFINITION_H
#define KH_RECODED_OV093_POPUP_DEFINITION_H

#include "nitro/types.h"

typedef struct PopupDefinition {
    s32 messageId;
    u32 category;
    u32 flags;
    u32 reserved;
} PopupDefinition;

extern PopupDefinition gTrophyEntryDefinitionsHead[];
#define gPopupDefinitions gTrophyEntryDefinitionsHead

#endif
