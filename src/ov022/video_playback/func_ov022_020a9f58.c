/* Returns the indexed word from a movie context table.
 * Evidence: Loads the index at +0x90 and returns the indexed word from the table at +0x88.
 * Uncertainty: The table entry contents and the table's higher-level role are unknown.
 * Source: khdays-decomp/src/overlays/ov024/auto/func_ov024_02085c7c.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
int func_ov022_020a9f58(const unsigned char *movieContext)
{
    int tableIndex = *(const int *)(movieContext + 0x90);
    const int *tableWords = (const int *)(movieContext + 0x88);
    return tableWords[tableIndex];
}
