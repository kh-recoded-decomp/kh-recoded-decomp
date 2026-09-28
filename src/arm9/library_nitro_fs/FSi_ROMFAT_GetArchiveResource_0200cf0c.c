#include "nitro/types.h"

#define FS_RESULT_SUCCESS 0

typedef struct RomHeader {
    u8 pad_00[0x80];
    u32 romSize;
} RomHeader;

typedef struct ArchiveResource {
    u64 totalSize;
    u64 availableSize;
    u32 maxFileHandles;
    u32 currentFileHandles;
    u32 maxDirectoryHandles;
    u32 currentDirectoryHandles;
    u32 bytesPerSector;
    u32 sectorsPerCluster;
    u32 totalClusters;
    u32 availableClusters;
} ArchiveResource;

extern const RomHeader *func_02009134(void);

int FSi_ROMFAT_GetArchiveResource_0200cf0c(void *archive, ArchiveResource *resource)
{
    const RomHeader *header = func_02009134();

    resource->bytesPerSector = 0;
    resource->sectorsPerCluster = 0;
    resource->totalClusters = 0;
    resource->availableClusters = 0;
    resource->totalSize = header->romSize;
    resource->availableSize = 0;
    resource->maxFileHandles = 0x7FFFFFFF;
    resource->currentFileHandles = 0;
    resource->maxDirectoryHandles = 0x7FFFFFFF;
    resource->currentDirectoryHandles = 0;
    return FS_RESULT_SUCCESS;
}
