typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int fx32;

typedef struct ScriptOperand {
    short type;
    u8 payload[6];
} ScriptOperand;

typedef struct ActorVector {
    fx32 x, y, z;
} ActorVector;

typedef struct ActorNodeObserved {
    u32 flags;
    u16 stateFlags;
    u8 unknown006[0x76];
    void *modelResource;
    u16 rotation;
    u8 unknown082[0x26];
    ActorVector position;
    u8 unknown0b4[0x20];
} ActorNodeObserved;

typedef struct MtxFx43 {
    fx32 row[4][3];
} MtxFx43;

extern int Script_ReadInteger_02025de4(void *scriptContext, ScriptOperand *operand);
extern fx32 Script_ReadFixed_02025df8(void *scriptContext, ScriptOperand *operand);
extern int Script_PassThroughActorId_02025960(void *scriptContext, int actorId);
extern void *GetSharedCommandDataOffset44_0208bcf8(void);
extern ActorNodeObserved *Actor_GetById_02036240(u32 actorId);
extern void InitRotationMatrix_01ff9480(MtxFx43 *matrix);
extern void BuildSineCosineRotationMatrix_01ff9530(MtxFx43 *matrix, int sine, int cosine);
extern void MTX_MultVec43_01ff9ad8(const ActorVector *vector, const MtxFx43 *matrix, ActorVector *result);
extern void AddActorVectors_01ff9e0c(const ActorVector *left, const ActorVector *right, ActorVector *result);
extern void func_020359f8(u32 actorId, int mode, const ActorVector *position);
extern void func_02036120(u32 actorId, int flag);
extern void UpdateActorCommand_ov001_0208c2c4(void *scriptContext, int mode, const ActorVector *position, u32 actorId);
extern short data_0205356c[];

int PlaceActorRelativeToActor_0208df48(void *scriptContext, ScriptOperand *commandOperands) {
    int actorToPlace;
    int referenceActor;
    fx32 verticalOffset;
    u32 resolvedActor;
    ActorVector sharedOrientation;
    ActorVector referencePosition;
    MtxFx43 rotationMatrix;
    ActorVector placementOffset;
    ActorNodeObserved *referenceNode;
    ActorNodeObserved *placedNode;
    int angleIndex;
    int forwardDistance;
    u16 heading;

    actorToPlace = Script_ReadInteger_02025de4(scriptContext, commandOperands);
    referenceActor = Script_ReadInteger_02025de4(scriptContext, commandOperands + 1);
    verticalOffset = Script_ReadFixed_02025df8(scriptContext, commandOperands + 2);
    resolvedActor = (u32)Script_PassThroughActorId_02025960(scriptContext, actorToPlace);
    sharedOrientation = *(ActorVector *)GetSharedCommandDataOffset44_0208bcf8();
    referenceNode = Actor_GetById_02036240((u32)referenceActor & 0xffff);
    referencePosition = referenceNode->position;
    forwardDistance = commandOperands[3].type == 0 ? verticalOffset :
        Script_ReadFixed_02025df8(scriptContext, commandOperands + 3);
    heading = (u16)sharedOrientation.x;
    placementOffset.x = 0;
    placementOffset.y = verticalOffset;
    placementOffset.z = forwardDistance;
    InitRotationMatrix_01ff9480(&rotationMatrix);
    angleIndex = (int)heading >> 4;
    BuildSineCosineRotationMatrix_01ff9530(&rotationMatrix,
        data_0205356c[angleIndex], data_0205356c[(0x400U - (u32)angleIndex) & 0xfff]);
    MTX_MultVec43_01ff9ad8(&placementOffset, &rotationMatrix, &placementOffset);
    placementOffset.x = -placementOffset.x;
    AddActorVectors_01ff9e0c(&referencePosition, &placementOffset, &referencePosition);
    func_020359f8(resolvedActor & 0xffff, 0, &referencePosition);
    placedNode = Actor_GetById_02036240(resolvedActor & 0xffff);
    if ((placedNode->flags & 0x20) == 0) {
        placedNode->rotation = heading;
        placedNode->stateFlags |= 0x20;
    }
    func_02036120(resolvedActor & 0xffff, 1);
    UpdateActorCommand_ov001_0208c2c4(scriptContext, 0, &referencePosition, resolvedActor);
    return 1;
}
