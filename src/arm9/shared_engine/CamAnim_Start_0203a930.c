#include "nitro/types.h"

typedef struct {
    u32 flags;
    void *resource;
    void *player;
    u8 pad_0c[0x3c];
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
} CameraAnim;

extern void *RetainOrInitializeSharedRecord_0202c80c(int fileId, int kind);
extern void *CamAnim_AllocPlayer_0203a920(void);
extern void CamAnim_SelectAnim_0203abac(CameraAnim *anim, int animIndex);
extern void CamAnim_ResetProjection_0203a8d8(CameraAnim *anim);
extern void func_0203aafc(CameraAnim *anim);

void CamAnim_Start_0203a930(CameraAnim *anim, int fileId)
{
    anim->flags = 0;
    anim->unk_54 = 0;
    anim->resource = RetainOrInitializeSharedRecord_0202c80c(fileId, 0x11);
    anim->player = CamAnim_AllocPlayer_0203a920();
    CamAnim_SelectAnim_0203abac(anim, 0);
    CamAnim_ResetProjection_0203a8d8(anim);
    func_0203aafc(anim);
    anim->unk_48 = 0;
    anim->unk_4C = 0;
    anim->unk_50 = 0;
    anim->flags |= 1;
}
