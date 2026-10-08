#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x66e8];
    s32 formatFailed;
} Panel;

extern void ShowTitleNotice(Panel *owner, int noticeType);

void ShowTitleFormatNotice(Panel *panel)
{
    int noticeType;

    if (panel->formatFailed == 0) {
        noticeType = 1;
    } else {
        noticeType = 2;
    }
    ShowTitleNotice(panel, noticeType);
}
