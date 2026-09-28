#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct Tween Tween;

extern void func_02052514(Tween *tween, int mode, fx32 startValue, fx32 endValue, int duration);
extern void func_0205255c(Tween *tween);

void StartUnitTween_020bf1f8(Tween *tween, int duration)
{
    func_02052514(tween, 0, 0, FX32_ONE, duration);
    func_0205255c(tween);
}
