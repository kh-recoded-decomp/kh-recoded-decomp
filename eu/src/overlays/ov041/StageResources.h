#ifndef STAGE_RESOURCES_H
#define STAGE_RESOURCES_H

#include "nitro/types.h"

typedef struct StageResourceHeader {
    u16 reserved00;
    u16 recordCount;
} StageResourceHeader;

typedef struct StageResourceContainer {
    StageResourceHeader *header;
    u8 cursor;
    u8 reserved05[3];
} StageResourceContainer;

typedef struct StageResourceItem {
    u32 reserved00;
    u8 model[0x138];
} StageResourceItem;

typedef struct StageResourceList {
    StageResourceItem *items;
    u8 count;
    u8 reserved05[3];
} StageResourceList;

typedef struct StageResourceGroup {
    StageResourceList *lists;
    u8 count;
    u8 reserved05[3];
} StageResourceGroup;

typedef struct StageResourceWork {
    u8 reserved000[0x19];
    u8 levelA;
    u8 levelB;
    u8 reserved01b[0x339];
    void *messages;
    StageResourceList *lists[0x3e];
    StageResourceGroup *groups[0x1b];
} StageResourceWork;

typedef struct StageResourceContext {
    u8 reserved000[0xb8];
    StageResourceWork *stageWork;
} StageResourceContext;

extern StageResourceContext *gMovieContextState;
void CreateStageResourceGroup(int category, StageResourceContainer *container);
void CreateStageResourceList(int index, int count, void *archive, u8 modelIndex, u8 blockIndex);

typedef char StageResourceListSize[sizeof(StageResourceList) == 8 ? 1 : -1];
typedef char StageResourceItemSize[sizeof(StageResourceItem) == 0x13c ? 1 : -1];
typedef char StageResourceListsOffset[(u32)&((StageResourceWork *)0)->lists == 0x358 ? 1 : -1];

#endif
