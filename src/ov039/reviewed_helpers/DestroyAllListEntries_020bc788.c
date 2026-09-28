extern int data_ov039_020bea00;
extern void *NNS_FndGetNextListObject_02012a38(void *list, void *obj);
extern void func_ov039_020bc70c(void *entry);

void DestroyAllListEntries_020bc788(void)
{
    void *entry = NNS_FndGetNextListObject_02012a38((void *)(data_ov039_020bea00 + 0xca74), 0);
    void *next;

    if (entry == 0) {
        return;
    }
    do {
        next = NNS_FndGetNextListObject_02012a38((void *)(data_ov039_020bea00 + 0xca74), entry);
        func_ov039_020bc70c(entry);
        entry = next;
    } while (next != 0);
}
