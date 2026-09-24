/* Initializes a six-by-three collection of entries and applies one stored state bit to each entry.
 * Reads eighteen packed bits using state ID 0x1e05, then maps bits 17 down to 0 to entry IDs 6 through 23 in six rows of three. Each entry is selected and receives its zero/one state through ov027 helpers.
 * The particular menu or scene shown by this overlay and the meaning of the eighteen stored state bits remain unconfirmed. No specific collectible, world or enemy is assigned.
 * Recovered from the persistent Ghidra caller chain and disassembly. */
typedef struct Overlay088GridSettings { int resource; int unknown[3]; } Overlay088GridSettings;
extern const Overlay088GridSettings defaultGridSettings;
extern const int gridEntryIds[6][3];
extern void *func_ov039_020bc1cc(void);
extern int func_ov039_020bc220(int group, int index);
extern void func_ov027_020b9060(void *grid, Overlay088GridSettings *settings);
extern void func_ov027_020b8f98(void *grid, int resource, int count);
extern void func_ov027_020b97fc(void *grid, int mode);
extern unsigned int func_ov001_02064574(int id, int bits);
extern int func_ov027_020b90a4(void *grid, int id);
extern void func_ov027_020b95e4(void *grid, int entry);
extern void func_ov027_020b96a0(void *grid, int entry, unsigned short state);
void ApplyOverlay088GridStates(void *unusedContext) {
    void *grid = func_ov039_020bc1cc();
    Overlay088GridSettings settings = defaultGridSettings;
    int stateBits;
    int row, column, entry;
    int enabled;
    settings.resource = func_ov039_020bc220(2, 0x13);
    func_ov027_020b9060(grid, &settings);
    func_ov027_020b8f98(grid, func_ov039_020bc220(2, 0x15), 0x18);
    func_ov027_020b97fc(grid, 2);
    stateBits = func_ov001_02064574(0x1e05, 18);
    for (row = 0; row < 6; ++row) {
        for (column = 0; column < 3; ++column) {
            if (stateBits & (1U << (17 - (column + row * 3)))) enabled = 1;
            else enabled = 0;
            entry = func_ov027_020b90a4(grid, gridEntryIds[row][column]);
            func_ov027_020b95e4(grid, entry);
            func_ov027_020b96a0(grid, entry, enabled);
        }
    }
}
