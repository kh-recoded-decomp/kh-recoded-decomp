/* Selects a tile-map entry from a packed coordinate and returns its high bit; game meaning unknown. Evidence: Source implementation directly performs the described operations; see src/auto/func_02025074.c. Uncertainty: The exact game-specific role is unresolved. Recovered from Days source src/auto/func_02025074.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
unsigned int func_0202ce18(unsigned int packed_coordinate) {
    unsigned int coordinate_mask = 0xfffffc;
    unsigned int map_row_address = (packed_coordinate >> 7 & coordinate_mask) + 0x1ff8000;
    unsigned short local_tile_index = packed_coordinate & (coordinate_mask >> 15);
    int row_header = *(unsigned short *)(map_row_address + 2) & (coordinate_mask >> 15);

    return *(unsigned int *)(map_row_address + ((unsigned int)(((row_header + 1) / 2) << 0x11) >> 0xf)
                                  + local_tile_index * 4 + 0x10) & 0x80000000;
}
