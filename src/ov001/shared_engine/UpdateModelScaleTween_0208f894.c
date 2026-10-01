#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ModelNode {
    u8 pad_00[0xb4];
    VecFx32 scale;
} ModelNode;

typedef struct ScaledModel {
    u8 pad_000[0x10];
    ModelNode node;
    u8 pad_0d0[0x2f0 - 0xd0];
    VecFx32 current;
    VecFx32 from;
    VecFx32 to;
    int elapsed;
    int duration;
    fx32 factor;
} ScaledModel;

extern int FixedPointMultiply12_02006450(int left, int right);
extern fx32 SafeFixedRatio_0208f868(fx32 numerator, fx32 denominator);
extern fx32 FixedPointLerp_0208f884(fx32 start, fx32 end, fx32 t);

void UpdateModelScaleTween_0208f894(ScaledModel *model, int step)
{
    ModelNode *node = &model->node;
    VecFx32 scale;
    int duration = model->duration;

    if (duration != 0) {
        fx32 t;
        model->elapsed += step;
        if (model->elapsed >= duration) {
            model->elapsed = duration;
        }
        t = SafeFixedRatio_0208f868(model->elapsed, model->duration);
        model->current.x = FixedPointLerp_0208f884(model->from.x, model->to.x, t);
        model->current.y = FixedPointLerp_0208f884(model->from.y, model->to.y, t);
        model->current.z = FixedPointLerp_0208f884(model->from.z, model->to.z, t);
        if (model->elapsed >= model->duration) {
            model->duration = 0;
        }
    }
    scale.x = FixedPointMultiply12_02006450(model->current.x, model->factor);
    scale.y = FixedPointMultiply12_02006450(model->current.y, model->factor);
    scale.z = FixedPointMultiply12_02006450(model->current.z, model->factor);
    node->scale = scale;
}
