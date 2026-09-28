#include "nitro/types.h"

typedef struct CursorSprite {
    u8 pad_00[0x30];
} CursorSprite;

typedef struct CursorTween {
    u8 pad_00[0x1c];
} CursorTween;

typedef struct TargetCursor {
    u8 pad_000[0xc0];
    CursorSprite sprites[2];
    CursorSprite *currentSprite;
    s32 targetChanged;
    void *target;
    CursorTween tween;
} TargetCursor;

extern BOOL func_ov001_0207fa2c(void *target);
extern void func_02052514(CursorTween *tween, int mode, s32 start, s32 end, s32 duration);
extern void func_0205255c(CursorTween *tween);

void SelectCursorTarget_0206bf7c(TargetCursor *cursor, void *target)
{
    int spriteIndex = 0;

    if (!func_ov001_0207fa2c(target)) {
        spriteIndex = 1;
    }
    if (cursor->target == target) {
        cursor->currentSprite = &cursor->sprites[spriteIndex];
        return;
    }
    cursor->target = target;
    cursor->targetChanged = 1;
    cursor->currentSprite = &cursor->sprites[spriteIndex];
    func_02052514(&cursor->tween, 2, 0x2d000, 0, 400);
    func_0205255c(&cursor->tween);
}
