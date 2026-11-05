#include "src/overlays/ov027/FileLoadQueue.h"

int UpdateFileLoadQueueTask(void)
{
    ProcessFileLoadQueue();
    return 0;
}
