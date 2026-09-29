#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xf064];
    BOOL isTouchScrolling;
} MenuScene;

extern void func_ov039_020bc03c(int value);

void StopTouchScrolling_020c0edc(MenuScene *scene)
{
    scene->isTouchScrolling = FALSE;
    func_ov039_020bc03c(FALSE);
}
