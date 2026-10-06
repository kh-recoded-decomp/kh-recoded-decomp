typedef struct {
    int a, b, c;
} IdTable;

extern void *data_ov015_0207e960;
extern IdTable data_ov015_02079f58;
extern void *FindWidgetById(void *target, int id);
extern void *func_ov027_020b9380(void *target, void *obj, int outVec[2], int mode);
extern void SetEntrySlotsVisible(void *target, void *obj, int flag);
extern void func_ov027_020b9604(void *target, void *obj);
extern void ApplySelectedSubitemValues(void *target, void *obj, int useAlt);
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
    obj = FindWidgetById(target, id);
    func_ov027_020b9380(target, obj, outVec, 0);

    target = (char *)data_ov015_0207e960 + 0x6ac0;
    obj = FindWidgetById(target, id);
    SetEntrySlotsVisible(target, obj, 1);

    target = (char *)data_ov015_0207e960 + 0x6ac0;
    obj = FindWidgetById(target, id);
    func_ov027_020b9604(target, obj);

    target = (char *)data_ov015_0207e960 + 0x6ac0;
    obj = FindWidgetById(target, id);
    ApplySelectedSubitemValues(target, obj, 1);

    func_ov015_0206f688(slotIndex, outVec);
}
