#include "src/filesystem/FileLoaderState.h"

void *gFileLoaderMessages[64];
u32 gFileLoaderThreadStorage[48];
FileLoaderMessageQueue gFileLoaderMessageQueue;
static u32 gResourcePaletteUploadCallbackStorage[4];
static u32 gTextureUploadCallback;
