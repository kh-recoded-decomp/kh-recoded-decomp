#ifndef STAGE_RESOURCES_H
#define STAGE_RESOURCES_H

#include "src/overlays/ov041/StageWork.h"

void CreateStageResourceGroup(int category, StageResourceContainer *container);
void CreateStageResourceList(int index, int count, void *archive, u8 modelIndex, u8 blockIndex);

#endif
