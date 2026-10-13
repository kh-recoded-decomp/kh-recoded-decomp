#include "src/overlays/ov004/ScrollTextImages.h"

extern void InitObjManager(ScrollImageList *manager, ScrollImageListConfig *config);
extern s32 end_key_share_and_register_result(ScrollImageList *manager, int value);

void InitScrollTextImageLists(void)
{
    ScrollImageListConfig config;
    int line;

    config.resourceKey = (((gScrollTextGlobals.work->messageResource + 0x8000) & 0x00fffffc) << 7) | 0x80000005;
    config.engine = 1;
    config.options = 0;
    config.reserved = 0;
    InitObjManager(&gScrollTextGlobals.work->mainImages, &config);
    config.engine = 2;
    InitObjManager(&gScrollTextGlobals.work->subImages, &config);
    for (line = 0; line < 4; line++) {
        gScrollTextGlobals.work->mainLineHandles[line] = end_key_share_and_register_result(&gScrollTextGlobals.work->mainImages, line);
        gScrollTextGlobals.work->subLineHandles[line] = end_key_share_and_register_result(&gScrollTextGlobals.work->subImages, line);
    }
}
