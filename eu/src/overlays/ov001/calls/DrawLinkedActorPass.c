#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct LinkedFieldObject LinkedFieldObject;
typedef struct FieldObjectClass {
    u8 pad_00[0x3c];
    void (*draw)(LinkedFieldObject *object);
    u8 pad_40[0x26];
    s16 animIndex;
} FieldObjectClass;

struct LinkedFieldObject {
    u8 pad_00[8];
    FieldObjectClass *objectClass;
    u8 pad_0c[0x30];
    s16 probeRadius;
    u8 pad_3e[0x10];
    u16 flags;
};

typedef struct ShadowVolume {
    VecFx32 position;
    fx32 scale;
    void *modelRef;
    u8 alpha;
    u8 pad_15;
    u16 rotY;
} ShadowVolume;

typedef struct FieldLinkTarget {
    u8 kind;
    u8 group;
    u8 index;
} FieldLinkTarget;

typedef struct LinkedActor {
    u8 pad_00[0x14];
    u8 sceneNode[0xa4];
    VecFx32 position;
    u8 pad_c4[0xe0];
    FieldLinkTarget link;
    u8 pad_1a7;
    ShadowVolume shadow;
} LinkedActor;

typedef struct ShadowSceneNode {
    u8 pad_00[0xa4];
    VecFx32 translation;
    fx32 scaleX;
    fx32 scaleY;
    fx32 scaleZ;
} ShadowSceneNode;

enum { FIELD_OBJECT_VOLUME_SHADOW = 0x80 };

typedef char ShadowVolumeSizeCheck[(sizeof(ShadowVolume) == 0x18) ? 1 : -1];

extern LinkedFieldObject *QueryLinkTarget(LinkedActor *actor);
extern BOOL func_ov001_0207ef90(void);
extern void DrawLodSceneObject(LinkedFieldObject *object);
extern void SceneNode_Draw(void *node);
extern void ShadowVolume_Draw(ShadowVolume *shadow);
extern ShadowSceneNode *func_ov001_0207f0c0(void);

void DrawLinkedActorPass(LinkedActor *actor, int pass)
{
    LinkedFieldObject *object = QueryLinkTarget(actor);
    ShadowSceneNode *shadowNode;
    VecFx32 position;

    if (pass == 0) {
        if (func_ov001_0207ef90()) {
            return;
        }
        if (object->objectClass->draw != NULL) {
            object->objectClass->draw(object);
        } else if (object->objectClass->animIndex >= 0) {
            DrawLodSceneObject(object);
        } else {
            SceneNode_Draw(actor->sceneNode);
        }
    } else if (object->flags & FIELD_OBJECT_VOLUME_SHADOW) {
        actor->shadow.position = actor->position;
        ShadowVolume_Draw(&actor->shadow);
    } else {
        shadowNode = func_ov001_0207f0c0();
        if (shadowNode != NULL) {
            position = actor->position;
            position.y += 0x40;
            shadowNode->translation = position;
            shadowNode->scaleZ = object->probeRadius;
            shadowNode->scaleY = shadowNode->scaleZ;
            shadowNode->scaleX = shadowNode->scaleY;
            SceneNode_Draw(shadowNode);
        }
    }
}
