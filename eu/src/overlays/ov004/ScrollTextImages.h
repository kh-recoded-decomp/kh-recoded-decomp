#ifndef SCROLL_TEXT_IMAGES_H
#define SCROLL_TEXT_IMAGES_H

#include "nitro/types.h"

/* InitObjManager clears this complete range before configuring the list.
 * The internal entry and slot layouts are not needed by this initializer. */
typedef struct {
    u8 reserved[0x6434];
} ScrollImageList;

typedef struct {
    u32 resourceKey;
    u32 engine;
    u32 options;
    u32 reserved;
} ScrollImageListConfig;

typedef struct {
    u8 reserved00[0xc];
    u32 messageResource;
    u8 reserved10[0x10918 - 0x10];
    s32 mainLineHandles[4];
    u8 reserved10928[0x21258 - 0x10928];
    s32 subLineHandles[4];
    u8 reserved21268[0x23ad4 - 0x21268];
    ScrollImageList mainImages;
    ScrollImageList subImages;
} ScrollTextImageWork;

typedef struct {
    u32 frameCount;
    ScrollTextImageWork *work;
    u32 reserved08[6];
} ScrollTextGlobals;

typedef char ScrollImageListSizeCheck[(sizeof(ScrollImageList) == 0x6434) ? 1 : -1];
typedef char ScrollImageListConfigSizeCheck[(sizeof(ScrollImageListConfig) == 16) ? 1 : -1];
typedef char ScrollTextGlobalsSizeCheck[(sizeof(ScrollTextGlobals) == 32) ? 1 : -1];

extern ScrollTextGlobals gScrollTextGlobals;

#endif
