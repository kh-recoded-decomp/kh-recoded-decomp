/* Fills a tile/palette rectangle and remaps coordinates for large background maps.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/func_02014174.c.
 * Original routine: func_02014174. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef unsigned short u16;

extern void func_02017b8c(u16 *dst, int width, int height, int mapW,
                          int tile, int palette);

void FillBackgroundTileRectangle_02017adc(u16 *dst, int width, int height, int x, int y,
                   int mapW, int tile, int palette)
{
    if (mapW <= 32) {
        int offset = mapW * y + x;
        func_02017b8c(dst + offset,
                      width, height, mapW, tile, palette);
    } else {
        int xEnd = x + width;
        int yEnd = y + height;
        u16 palBits = (u16)(palette << 12);

        for (; y < yEnd; y++) {
            int drawX;
            int rowIndex = y < 32 ? y : y + 32;
            u16 *row = dst + rowIndex * 32;

            for (drawX = x; drawX < xEnd; drawX++) {
                int columnIndex = drawX < 32 ? drawX : drawX + 0x3e0;
                row[columnIndex] = (u16)(tile++ | palBits);
            }
        }
    }
}
