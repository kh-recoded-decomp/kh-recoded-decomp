#include "src/overlays/ov001/StageObjectList.h"

StageObjectEntry *GetStageObjectEntry(int index)
{
    return &gStageObjectList->entries[index];
}
