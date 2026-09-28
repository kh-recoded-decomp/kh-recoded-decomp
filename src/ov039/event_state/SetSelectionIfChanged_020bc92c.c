extern int data_ov039_020bea00;
extern void func_ov039_020bb824(int base, int kind);
extern void func_ov039_020bb754(int base, int kind, int id);

void SetSelectionIfChanged_020bc92c(int id)
{
    int base = data_ov039_020bea00;

    if (id == *(int *)(base + 0xc994)) {
        return;
    }
    func_ov039_020bb824(base, 2);
    func_ov039_020bb754(base, 2, id);
    *(int *)(base + 0xc994) = id;
}
