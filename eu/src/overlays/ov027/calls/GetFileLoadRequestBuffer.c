#include "src/overlays/ov027/FileLoadQueue.h"

void *GetFileLoadRequestBuffer(const FileLoadRequest *request)
{
    return request->buffer;
}
