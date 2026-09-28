extern void Slot_UnlinkIfLinked(void *p, int idx);

void Slot_UnlinkAll_0204f104(void *p)
{
    int i;
    for (i = 0; i < 0x80; i++) {
        Slot_UnlinkIfLinked(p, i);
    }
}
