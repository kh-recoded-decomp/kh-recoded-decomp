#ifndef EU_SCENE_TASK_TABLES_H
#define EU_SCENE_TASK_TABLES_H

#include "src/overlays/ov001/StageActorTables.h"

/* -1 means the task has not been created or has already been released. */
extern u32 gSubScene9TaskHandle;
extern u32 gRootObjectTaskHandle;
extern u32 gEventTriggerTaskHandle;
extern u32 gScreenFadeTaskHandle;
extern StageManagerTaskDescriptor gSubScene9TaskDescriptor;
extern StageManagerTaskDescriptor gRootObjectTaskDescriptor;
extern StageManagerTaskDescriptor gEventTriggerTaskDescriptor;
extern StageManagerTaskDescriptor gScreenFadeTaskDescriptor;
extern char gSessionArchiveName[4];

#endif
