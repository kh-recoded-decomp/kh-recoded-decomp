#ifndef OV101_PAGE_SCROLL_STATE_H
#define OV101_PAGE_SCROLL_STATE_H

#include "nitro/fx_types.h"
#include "nitro/types.h"

typedef struct {
    fx32 target;
    fx32 current;
} PageScrollValue;

typedef struct {
    u8 pad_0000[0xDBCC];
    PageScrollValue pageScroll[1];
} Ov101PageScrollState;

extern Ov101PageScrollState *data_ov101_020c5920;

#endif
