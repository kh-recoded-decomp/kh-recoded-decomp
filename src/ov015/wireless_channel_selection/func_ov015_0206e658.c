typedef struct {
    int a, b, c;
} IdTable;

extern void *data_ov015_0207e960;
extern IdTable data_ov015_02079f58;
extern void *func_ov027_020b90a4(void *target, int id);
extern void *func_ov027_020b9360(void *target, void *obj, int outVec[2], int mode);
extern void func_ov027_020b9580(void *target, void *obj, int flag);
extern void func_ov027_020b95e4(void *target, void *obj);
extern void ApplySelectedSubitemValues_020b94fc(void *target, void *obj, int useAlt);
extern void func_ov015_0206f688(int param, int outVec[2]);

void func_ov015_0206e658(int slotIndex) {
    IdTable ids;
    int id;
    void *obj;
    void *target;
    int outVec[2];

    ids = data_ov015_02079f58;
    id = ((int *)&ids)[slotIndex];

    target = (char *)data_ov015_0207e960 + 0x6ac0;
    obj = func_ov027_020b90a4(target, id);
    func_ov027_020b9360(target, obj, outVec, 0);

    target = (char *)data_ov015_0207e960 + 0x6ac0;
    obj = func_ov027_020b90a4(target, id);
    func_ov027_020b9580(target, obj, 1);

    target = (char *)data_ov015_0207e960 + 0x6ac0;
    obj = func_ov027_020b90a4(target, id);
    func_ov027_020b95e4(target, obj);

    target = (char *)data_ov015_0207e960 + 0x6ac0;
    obj = func_ov027_020b90a4(target, id);
    ApplySelectedSubitemValues_020b94fc(target, obj, 1);

    func_ov015_0206f688(slotIndex, outVec);
}
