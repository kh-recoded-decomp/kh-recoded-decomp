#include "src/SaveIoState.h"

void SetCardThreadDoneCallback(void)
{
    data_0205fe00.doneCallback = BeginSaveSlotWrite;
}
