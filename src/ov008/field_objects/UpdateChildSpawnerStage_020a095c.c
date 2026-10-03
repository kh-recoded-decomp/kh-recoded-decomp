#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x4];
    u16 anim;
} AnimBody;

typedef struct {
    u8 pad_00[0x10];
    AnimBody body;
} SpawnerEntry;

typedef struct FieldObject {
    u8 pad_00[0xc];
    SpawnerEntry *entry;
    u8 pad_10[0x43];
    s8 stage;
    u8 pad_54[0x10];
    fx32 frame;
} FieldObject;

extern const s16 data_ov008_020a13e0[];
extern BOOL AdvanceAnimFrame_02080a38(void *anim, fx32 step, BOOL loop, fx32 length, fx32 *frame);
extern void FieldObject_SetSavedValue_0207f9c8(FieldObject *object, u32 value);
extern u16 FieldObject_GetSavedValue_0207f9a8(FieldObject *object);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern void func_0202f4d8(void *anim);

int UpdateChildSpawnerStage_020a095c(FieldObject *object)
{
    AnimBody *body = &object->entry->body;
    s16 length = data_ov008_020a13e0[object->stage];

    if (length == 1) {
        AdvanceAnimFrame_02080a38(&body->anim, 0x1000, TRUE, length << 12, &object->frame);
    } else if (!AdvanceAnimFrame_02080a38(&body->anim, 0x1000, FALSE, length << 12, &object->frame)) {
        object->stage++;
        FieldObject_SetSavedValue_0207f9c8(object, object->stage);
        RebindAnimTracks_020809d0(&object->entry->body.anim, object->stage, 0);
        object->frame = 0;
        func_0202f4d8(&object->entry->body.anim);
    }
    if (object->stage != FieldObject_GetSavedValue_0207f9a8(object)) {
        object->stage = FieldObject_GetSavedValue_0207f9a8(object);
        RebindAnimTracks_020809d0(&object->entry->body.anim, object->stage, 0);
        object->frame = 0;
        func_0202f4d8(&object->entry->body.anim);
    }
    return 0;
}
