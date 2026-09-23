/* Extracts a requested-width field from an MSB-first packed word array. Evidence: Source implementation directly performs the described operations; see src/auto/func_020256b8.c. Uncertainty: No material uncertainty for the stated operation; game-specific use may depend on callers. Recovered from Days source src/auto/func_020256b8.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
typedef unsigned int u32;
u32 ReadPackedBitField_0202d4c4(u32 *words, u32 start_bit, u32 field_width)
{
    u32 field_value = 0;
    u32 field_mask;
    u32 bits_this_word;
    words += (int)start_bit / 32;
    start_bit &= 0x1f;
    if ((int)(start_bit + field_width) > 0x20) {
        do {
            bits_this_word = 0x20 - start_bit;
            field_mask = (bits_this_word == 0x20) ? 0xffffffff : (1u << bits_this_word) - 1;
            field_width -= bits_this_word;
            field_value = (*words++ & field_mask) | (field_value << bits_this_word);
            start_bit = 0;
        } while ((int)field_width > 0x20);
    }
    if ((int)field_width > 0) {
        field_mask = (field_width == 0x20) ? 0xffffffff : (1u << field_width) - 1;
        field_value = (field_mask & (*words >> ((0x20 - start_bit) - field_width))) | (field_value << field_width);
    }
    return field_value;
}
