#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x830];
    u8 textLayer[0x50];
    int captionDirty;
    u8 pad_884[0x38];
    int hasCaption;
    u8 topLayout[0x100];
    u8 bottomLayout[0x100];
} MoviePlayer;

extern MoviePlayer *data_ov022_020b7d80;
extern const char *data_ov022_020b7bf8[];

extern void ResetSubtitleLine_020a8a50(void *stream);
extern void func_ov022_020a90f8(void *stream, void *layout);
extern u32 func_0202b788(void);
extern int Utf8ToUcs2_020512b4(const char *src, u16 *dst, int maxChars);
extern void DrawTextAnchored_020015a0(void *window, int x, int y, int color, int flags, const void *text);
extern void UploadDirtySubtitleTiles_020a914c(void *stream);

void DrawMovieCaption_020a6f68(BOOL top) {
    MoviePlayer *player = data_ov022_020b7d80;
    void *layout = top ? player->topLayout : player->bottomLayout;
    u16 text[0x40];

    ResetSubtitleLine_020a8a50(player->textLayer);
    func_ov022_020a90f8(player->textLayer, layout);
    if (player->hasCaption) {
        u32 language = func_0202b788();

        player->captionDirty = 0;
        Utf8ToUcs2_020512b4(data_ov022_020b7bf8[language], text, 0x40);
        DrawTextAnchored_020015a0(player->textLayer, 0xfd, 3, 1, 0x20, text);
    }
    UploadDirtySubtitleTiles_020a914c(player->textLayer);
}
