#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Particle {
    fx32 sinAngle;
    fx32 cosAngle;
    u8 pad08[0xc];
    VecFx32 position;
    VecFx32 origin;
    VecFx32 velocity;
    VecFx32 savedOrigin;
    VecFx32 savedPosition;
} Particle;

typedef struct EventCameraWork {
    VecFx32 position;
    u8 pad00c[0xc];
    VecFx32 velocity;
    fx32 rotateSpeed;
    u8 pad028[0x168];
    VecFx32 offset;
} EventCameraWork;

extern const s16 data_0205356c[];
extern void func_ov046_020c2cb8(VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(VecFx32 *in, VecFx32 *out);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void InitDriftParticleMotion_020afa40(Particle *particle, const VecFx32 *origin, const VecFx32 *offset, const VecFx32 *velocity);

#define SPEED_TO_INDEX(speed) ((s32)((((s64)(speed) << 16) / 0x6488) & 0xffff) >> 4)

void UpdateEventCameraOrbitParticle_020c4104(EventCameraWork *work, Particle *particle)
{
    VecFx32 pos;
    VecFx32 focus;
    VecFx32 focusTmp;
    VecFx32 scaledArg;
    VecFx32 normTmp;
    VecFx32 deltaTmp;
    VecFx32 delta;
    VecFx32 dir;
    VecFx32 scaled;
    fx32 length;

    pos = work->position;
    func_ov046_020c2cb8(&focusTmp);
    focus = focusTmp;
    VEC_Subtract_01ff9e3c(&focus, &pos, &deltaTmp);
    delta = deltaTmp;
    length = func_01ffaff4(&delta, &normTmp);
    dir = normTmp;
    if (length < 0xc00) {
        scaled = dir;
        ScaleVecFx32InPlace_0204a5e4(&scaled, -0xc00);
        scaledArg = scaled;
        VEC_Add_01ff9e0c(&scaledArg, &focus, &pos);
    }
    InitDriftParticleMotion_020afa40(particle, &pos, &work->offset, &work->velocity);
    particle->savedOrigin = particle->origin;
    particle->savedPosition = particle->position;
    particle->sinAngle = data_0205356c[SPEED_TO_INDEX(work->rotateSpeed)];
    particle->cosAngle = data_0205356c[(0x400 - SPEED_TO_INDEX(work->rotateSpeed)) & 0xfff];
}
