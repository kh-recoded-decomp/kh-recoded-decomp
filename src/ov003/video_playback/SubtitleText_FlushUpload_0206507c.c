#include "nitro/types.h"

typedef struct SubtitleTextRenderer {
    u8 pad_00[0x44];
    BOOL uploadPending;
} SubtitleTextRenderer;

extern void Text_UploadTileBuffer_02001520(SubtitleTextRenderer *renderer);

void SubtitleText_FlushUpload_0206507c(SubtitleTextRenderer *renderer)
{
    if (!renderer->uploadPending) {
        return;
    }
    Text_UploadTileBuffer_02001520(renderer);
    renderer->uploadPending = FALSE;
}
