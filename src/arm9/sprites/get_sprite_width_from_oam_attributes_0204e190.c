/* Returns a sprite's pixel width from the packed DS OAM shape and size attributes.
 * Evidence: The code reads attribute bits 14-15 and 30-31; the shared 12-entry OAM size table
 * identifies the result groups as widths 8, 16, 32, and 64 pixels.
 * Uncertainty: The target call sites should still confirm which attribute word is supplied.
 * Source: src/auto/func_02031730.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */

int get_sprite_width_from_oam_attributes_0204e190(int *spriteAttributes) {
    switch (*spriteAttributes & (int)0xc000c000) {
    case 0x00000000:
    case 0x00008000:
    case 0x40008000:
        return 8;
    case 0x00004000:
    case 0x40000000:
    case (int)0x80008000:
        return 0x10;
    case 0x40004000:
    case (int)0x80000000:
    case (int)0x80004000:
    case (int)0xc0008000:
        return 0x20;
    case (int)0xc0000000:
    case (int)0xc0004000:
        return 0x40;
    }
    return 0;
}
