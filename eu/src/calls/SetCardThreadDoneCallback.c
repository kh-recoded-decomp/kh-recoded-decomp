#include "src/SaveIoState.h"

void SetCardThreadDoneCallback(void)
{
    gSaveIoStatePrefix.doneCallback = BeginSaveSlotWrite;
}
