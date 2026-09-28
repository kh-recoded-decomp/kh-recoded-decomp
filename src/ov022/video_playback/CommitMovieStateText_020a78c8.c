#include "nitro/types.h"

typedef struct MovieOverlayState {
    u8 pad_000[0x8b5];
    u8 textVisible;
    u8 pad_8b6[0x8c0 - 0x8b6];
    char currentText[0x100];
    char savedText[0x100];
} MovieOverlayState;

extern MovieOverlayState *data_020b7d80;
extern char *strcpy_02021e60(char *dst, const char *src);
extern void func_ov022_020a6f68(BOOL useCurrentText);

void CommitMovieStateText_020a78c8(void)
{
    strcpy_02021e60(data_020b7d80->savedText, data_020b7d80->currentText);
    func_ov022_020a6f68(TRUE);
    data_020b7d80->textVisible = TRUE;
}
