/* Fills a 14-word block with fixed-point projection and clipping defaults. Evidence: Source implementation directly performs the described operations; see src/auto/func_02023c60.c. Uncertainty: No material uncertainty for the stated operation; game-specific use may depend on callers. Recovered from Days source src/auto/func_02023c60.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
void LoadDefaultProjectionValues_0202a7b4(unsigned int *projection_values) {
    projection_values[0]  = 0x800;
    projection_values[1]  = 0xddb;
    projection_values[2]  = 0x1555;
    projection_values[3]  = 0x1000;
    projection_values[4]  = 0x3e8000;
    projection_values[5]  = projection_values[6] = projection_values[7] = 0;
    projection_values[8]  = projection_values[9] = 0;
    projection_values[10] = 0x64000;
    projection_values[11] = projection_values[13] = 0;
    projection_values[12] = 0x1000;
}
