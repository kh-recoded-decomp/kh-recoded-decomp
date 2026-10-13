#ifndef KH_RECODED_ROOT_MENU_H
#define KH_RECODED_ROOT_MENU_H

#include "nitro/types.h"

typedef struct RootMenuEntry {
    u16 *label;
    u16 *description;
    s32 sceneId;
} RootMenuEntry;

typedef struct RootMenu {
    u8 cursor;
    u8 entryCount;
    u8 state;
    u8 mode;
    u8 optionCursor;
    u8 cursorVisible;
    u8 reserved06[0x10 - 6];
    u16 revealTimer;
    u16 unlockMessage;
    u8 reserved14[0x508 - 0x14];
    RootMenuEntry entries[8];
    u16 *extraLabels[4];
    u8 reserved578[4];
    void *objManager;
    u8 reserved580[0x5c0 - 0x580];
    int cursorElement;
    int headerElement;
    int frameElement;
    u8 reserved5cc[0x5e8 - 0x5cc];
} RootMenu;

extern void *gRootMenuDefinition[17];
void HandleRootMenuConfirm(RootMenu *menu);

#endif
