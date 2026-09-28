extern void Slot_UnlinkAll(void *);
extern void SlotNodeList_FreeAll(void *);

int Obj_Release_0204eff8(void *object)
{
    Slot_UnlinkAll(object);
    SlotNodeList_FreeAll(object);
    return 1;
}
