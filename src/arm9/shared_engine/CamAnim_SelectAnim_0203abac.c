#include "nitro/types.h"
#include "nnsys/g3d.h"

typedef struct CameraAnimResource {
    u8 pad_00[0xc];
    void *anmSet;
} CameraAnimResource;

typedef struct CameraAnim {
    u32 unk_00;
    CameraAnimResource *resource;
    NNSG3dAnmObj *anmObj;
} CameraAnim;

extern NNSG3dFuncAnmJnt data_02055cf8;
extern void *GetAnimationSetResourceByIndex_0201acb0(const void *res, u32 idx);
extern void MIi_CpuClear16_01ff8684(u16 data, void *dest, u32 size);
extern void Obj_SetIndirectWord_0203ab94(CameraAnim *anim, int value);

void CamAnim_SelectAnim_0203abac(CameraAnim *anim, u32 index)
{
    u32 i;
    NNSG3dResJntAnm *jntAnm = GetAnimationSetResourceByIndex_0201acb0(anim->resource->anmSet, index);
    NNSG3dAnmObj *anmObj = anim->anmObj;
    u16 *ofsArray;

    anmObj->frame = 0;
    anmObj->next = NULL;
    anmObj->priority = 0x7f;
    anmObj->ratio = FX32_ONE;
    anmObj->resTex = NULL;
    anmObj->resAnm = jntAnm;
    anmObj->funcAnm = data_02055cf8;
    anmObj->numMapData = 2;
    MIi_CpuClear16_01ff8684(0, &anmObj->mapData[0], sizeof(u16) * anmObj->numMapData);
    ofsArray = (u16 *)((u8 *)jntAnm + sizeof(NNSG3dResJntAnm));
    for (i = 0; i < jntAnm->numNode; i++) {
        NNSG3dResJntAnmSRTTag *tag = (NNSG3dResJntAnmSRTTag *)((u8 *)jntAnm + ofsArray[i]);
        anmObj->mapData[i] = (u16)((tag->tag >> NNS_G3D_JNTANM_SRTINFO_NODE_SHIFT) | NNS_G3D_ANMOBJ_MAPDATA_EXIST);
    }
    Obj_SetIndirectWord_0203ab94(anim, 0);
}
