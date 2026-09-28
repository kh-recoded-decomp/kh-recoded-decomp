extern int func_02025de4(int scriptContext, void *operand);
extern int func_02021948(int scriptContext, void *operand);
extern int func_02025960(int scriptContext, int operandArgument);
extern char *func_02036240(int index);

extern void Model_SetAllMaterialAlpha(int modelResource, int value);
extern void Model_SetAllPolygonIds(int modelResource, int value);

typedef struct { int x, y, z; } ActorNodeOffset;

int Script_MakeActorTranslucentAndClearVerticalOffset_0208deb0(int scriptContext, int commandOperands) {
    char *actorNode = func_02036240((unsigned short)func_02025960(scriptContext, func_02025de4(scriptContext, (void *)commandOperands)));
    ActorNodeOffset offset;
    offset.x = *(int *)(actorNode + 0xb4);
    offset.y = 0;
    offset.z = *(int *)(actorNode + 0xbc);
    *(ActorNodeOffset *)(actorNode + 0xb4) = offset;
    Model_SetAllMaterialAlpha(*(int *)(actorNode + 0x7c), 8);
    Model_SetAllPolygonIds(*(int *)(actorNode + 0x7c), 0x3f);
    return 1;
}
