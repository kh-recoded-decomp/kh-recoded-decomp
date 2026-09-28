#include "nitro/types.h"
#include "nitro/os.h"
#include "nnsys/g2d.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

extern GXBGAreaOver data_0205a920;
typedef struct ScreenSizeMap {
    u16 width;
    u16 height;
    u16 scnSize;
} ScreenSizeMap;
extern const ScreenSizeMap data_0205301c[4];
extern GXBGAreaOver data_0205a920;
extern const ScreenSizeMap * SelectScnSize (const ScreenSizeMap tbl[4], int w, int h);
extern void SetBGnControlToAffine (NNSG2dBGSelect n, GXBGScrSizeAffine size, GXBGAreaOver areaOver, GXBGScrBase scnBase, GXBGCharBase chrBase);

void SetBGControlAffine_020160dc (NNSG2dBGSelect bg, int screenWidth, int screenHeight, GXBGScrBase scnBase, GXBGCharBase chrBase)
{
    const ScreenSizeMap * pSizeMap;

    pSizeMap = SelectScnSize(data_0205301c, screenWidth, screenHeight);

    SetBGnControlToAffine(bg, (GXBGScrSizeAffine)pSizeMap->scnSize, data_0205a920, scnBase, chrBase);
}
