extern int ScriptVm_ReadOperandInt(void *self, void *desc);
extern int ByteCode_ResolveOperand(void *self, void *desc);
extern void Ov002_SpawnStateSpots(int a, int b, int c, int d);

int ScriptCmd_SpawnStateSpot_02080140(void *self, char *descs) {
    int a = ScriptVm_ReadOperandInt(self, descs);
    int b = ScriptVm_ReadOperandInt(self, descs + 8);
    int c = ByteCode_ResolveOperand(self, descs + 0x10);
    int d = ByteCode_ResolveOperand(self, descs + 0x18);

    Ov002_SpawnStateSpots(a, b, c, d);
    return 1;
}
