typedef struct ScriptVector {
    int x;
    int y;
    int z;
} ScriptVector;

extern int Script_ReadInteger(void *scriptContext, void *operand);
extern int Script_ReadFixed(void *scriptContext, void *operand);
extern void func_ov001_020725dc(const ScriptVector *vector, int operation);

int ScriptCmd_ApplyVectorOperation_020a0520(void *scriptContext, void *command)
{
    ScriptVector vector;
    int operation = Script_ReadInteger(scriptContext, command);

    vector.x = Script_ReadFixed(scriptContext, (char *)command + 8);
    vector.y = Script_ReadFixed(scriptContext, (char *)command + 0x10);
    vector.z = Script_ReadFixed(scriptContext, (char *)command + 0x18);
    func_ov001_020725dc(&vector, operation);
    return 1;
}
