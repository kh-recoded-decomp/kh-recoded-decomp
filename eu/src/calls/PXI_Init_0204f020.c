#include "nitro/types.h"

typedef struct ImageManager ImageManager;
extern int CreateImageEntry(ImageManager *manager, int fileId);

int PXI_Init_0204f020(void *manager, u32 imageKey)
{
    return CreateImageEntry(manager, (int)imageKey);
}
