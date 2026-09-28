#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x134];
    int pageIndex;
    u8 pad_138[0x154 - 0x138];
    BOOL sliderHeld;
} Ov086Menu;

extern Ov086Menu *data_ov086_020c3000;

void OnSliderTouched_020c2040(void)
{
    if (data_ov086_020c3000->pageIndex != 7) {
        data_ov086_020c3000->sliderHeld = TRUE;
    }
}
