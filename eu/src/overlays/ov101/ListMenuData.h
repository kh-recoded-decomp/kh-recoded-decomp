#ifndef KH_RECODED_LIST_MENU_DATA_H
#define KH_RECODED_LIST_MENU_DATA_H
#include "src/overlays/ov101/ListSceneState.h"

typedef struct ListScrollPanelConfig {
    s32 listId, pageRows, totalRows;
    s32 cursorEntry, upArrowEntry, downArrowEntry, barEntry;
    s32 thumbEntry, firstPipEntry, lastPipEntry, barEndEntry;
} ListScrollPanelConfig;

typedef struct ListEntryTextIndices {
    s32 nameIndex;
    s32 descriptionIndex;
} ListEntryTextIndices;

typedef struct ListSceneDescriptor {
    BOOL (*initialize)(ListSceneState *scene);
    void (*shutdown)(ListSceneState *scene);
    void (*update)(ListSceneState *scene);
    u32 parameter;
    u32 contextSize;
    void (*handlers[12])(void);
} ListSceneDescriptor;

extern ListScrollPanelConfig gPrimaryListScrollConfig;
extern ListScrollPanelConfig gSecondaryListScrollConfig;
extern ListEntryTextIndices gListEntryTextIndices[40];
extern ListSceneDescriptor gListSceneDescriptor;
extern const char *gListTextArchivePaths[4];
extern const char *gListMessageArchivePaths[5];
extern char sListBattleStringsPath[16];
extern char sListCharacterArchivePath[24];
extern char sListLocalizedCharacterArchivePath[28];
extern char sListStoryTextPath[28];
extern char sListLocalizedCharacterObjectArchivePath[32];

typedef char ListScrollConfigSizeCheck[(sizeof(ListScrollPanelConfig) == 44) ? 1 : -1];
typedef char ListSceneDescriptorSizeCheck[(sizeof(ListSceneDescriptor) == 68) ? 1 : -1];
#endif
