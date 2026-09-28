extern void *Ov008_FindEntryById(void *, void *);
extern void Ov008_StoreWordAt0x98(void *, void *);
void ResolveEntryStoreWord_020b9088(void *arg0, void *arg1, void *arg2)
{
    Ov008_StoreWordAt0x98(Ov008_FindEntryById(arg0, arg1), arg2);
}
