extern int data_ov039_020bea00;
extern void *NNS_FndGetNextListObject_02012a38(void *list, void *obj);
extern void RemoveIntrusiveListObject_020129d8(void *list, void *obj);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void RemoveListEntry_020bc70c(void *entry)
{
    void *current = NNS_FndGetNextListObject_02012a38((void *)(data_ov039_020bea00 + 0xca74), 0);

    while (current != 0) {
        if (current == entry) {
            RemoveIntrusiveListObject_020129d8((void *)(data_ov039_020bea00 + 0xca74), entry);
            if (entry != 0) {
                NNSi_FndFreeFromDefaultHeap_0202a1c4(entry);
            }
            return;
        }
        current = NNS_FndGetNextListObject_02012a38((void *)(data_ov039_020bea00 + 0xca74), current);
    }
}
