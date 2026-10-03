#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct HitInfo {
    u32 flags;
    VecFx32 contactPoint;
    VecFx32 sourcePosition;
    u8 pad_1c[0xc];
    s32 damage;
} HitInfo;

typedef struct Actor {
    u8 pad_0000[0x928];
    u64 statusFlags;
    u8 pad_0930[0x944 - 0x930];
    s32 mode;
    u8 pad_0948[4];
    VecFx32 guardPoint;
    u8 pad_0958[4];
    s32 guardTimer;
    u8 pad_0960[0x970 - 0x960];
    VecFx32 velocity;
    VecFx32 drift;
} Actor;

extern BOOL TryGuardFrontalHit_020c91fc(Actor *actor, HitInfo *hit);
extern void RollHitEffect_020a78b0(Actor *actor, HitInfo *hit);
extern int func_ov021_020a766c(Actor *actor, HitInfo *hit, BOOL critical);
extern BOOL AddClampedHealth_020a75ec(Actor *actor, int delta);
extern void IsMoviePlaybackIdle_020a78fc(Actor *actor, HitInfo *hit);
extern void func_ov059_020cd224(Actor *actor);
extern u32 random_next_scaled_0202aa04(u32 upperBound);
extern VecFx32 GetCameraOrbitOffset_020af8d4(fx32 radians);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void StartCameraParticle_020bcb38(const VecFx32 *launch, int param40, int param44, int param2c);
extern void func_ov059_020cb968(Actor *actor);

BOOL Actor_TakeHit_020ccae8(Actor *actor, HitInfo *hit)
{
    VecFx32 contact = hit->contactPoint;
    int damage;
    BOOL knockback;

    if (TryGuardFrontalHit_020c91fc(actor, hit)) {
        return TRUE;
    }
    if (actor->statusFlags & 0x820) {
        return FALSE;
    }
    if (!(hit->flags & 0x20)) {
        if (actor->guardTimer > 0) {
            return FALSE;
        }
        actor->guardTimer += 0x2d000;
    }
    RollHitEffect_020a78b0(actor, hit);
    damage = func_ov021_020a766c(actor, hit, actor->mode == 10);
    AddClampedHealth_020a75ec(actor, (s16)-damage);
    hit->damage = damage;
    IsMoviePlaybackIdle_020a78fc(actor, hit);
    knockback = TRUE;
    if (hit->flags & 0x10) {
        knockback = FALSE;
    }
    if (knockback) {
        int sign;
        VecFx32 launch;
        VecFx32 orbit;
        VecFx32 offset;

        actor->statusFlags |= 0x10;
        actor->guardPoint = contact;
        actor->velocity.z = 0;
        actor->velocity.y = 0;
        actor->velocity.x = 0;
        actor->drift.z = 0;
        actor->drift.y = 0;
        actor->drift.x = 0;
        func_ov059_020cd224(actor);
        sign = random_next_scaled_0202aa04(2) != 0 ? 1 : -1;
        orbit = GetCameraOrbitOffset_020af8d4(random_next_scaled_0202aa04(0x6488));
        offset = orbit;
        ScaleVecFx32InPlace_0204a5e4(&offset, 0x1ec);
        launch = offset;
        StartCameraParticle_020bcb38(&launch, 0x333, (int)((s64)sign * 0x430), 0xa000);
        func_ov059_020cb968(actor);
    }
    return TRUE;
}
