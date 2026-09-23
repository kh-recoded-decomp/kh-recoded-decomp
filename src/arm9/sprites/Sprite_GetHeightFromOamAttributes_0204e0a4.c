/* Behavior: Returns the pixel height of a sprite, such as a menu icon, from its stored shape and size settings.
 * Inputs/outputs and evidence: Bits 14-15 select OAM shape and bits 30-31 select size. All 12 supported cases match NNSi_objSizeHTbl in the reference Nitro G2D source.
 * Uncertainty: The height calculation is established. Specific icons or characters using this helper have not been traced.
 * Source: khdays-decomp/src/auto/func_02031644.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
int Sprite_GetHeightFromOamAttributes_0204e0a4(int *spriteAttributes) {
    switch (*spriteAttributes & (int)0xc000c000) {
    case 0x00000000:
    case 0x00004000:
    case 0x40004000:
        return 8;
    case 0x00008000:
    case 0x40000000:
    case (int)0x80004000:
        return 0x10;
    case 0x40008000:
    case (int)0x80000000:
    case (int)0x80008000:
    case (int)0xc0004000:
        return 0x20;
    case (int)0xc0000000:
    case (int)0xc0008000:
        return 0x40;
    }
    return 0;
}
