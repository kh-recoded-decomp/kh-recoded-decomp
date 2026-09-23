/* Behavior: Makes the actor model translucent and clears the actor node offset's Y component.
 * Inputs/outputs and evidence: Reads an entity index, preserves offset X/Z, writes Y zero, sets all material alpha values to 8, and sets all model polygon IDs to 0x3f.
 * Uncertainty: The reason for combining the vertical offset reset with these render settings is unknown.
 * Source: khdays-decomp/src/overlays/ov023/calls/func_ov023_020860b4.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
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
