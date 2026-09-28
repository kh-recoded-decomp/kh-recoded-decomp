struct S { char pad[0x74]; int field_74; };

void Slot_SetMode2Bit_0204f480(int *base, int index, int value)
{
    if (index < 0) return;
    *(int *)((char *)base + index * 0x8c + 0x74) = value & 3;
}
