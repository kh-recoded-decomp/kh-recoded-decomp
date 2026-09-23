/* Initializes graphics state values and identity matrices; several field meanings remain unknown. Evidence: Source implementation directly performs the described operations; see src/calls/func_02015630.c. Uncertainty: The exact game-specific role is unresolved. Recovered from Days source src/calls/func_02015630.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern void MTX_Identity33_(void *matrix_input);
extern void MTX_Identity43_(void *matrix_input);
extern void MTX_Identity44_(void *matrix_input);

extern struct {
    int unknownField00;
    int unknownField04;
    char _pad08[0x48 - 0x08];
    int unknownField48;
    char _pad4c[0x7c - 0x4c];
    int unknownField7C;
    int unknownField80;
    int unknownField84;
    int unknownField88;
    int unknownField8C;
    int unknownField90;
    char _pad94[0xb8 - 0x94];
    int translation_x;
    int translation_y;
    int translation_z;
    int scale_x;
    int scale_y;
    int scale_z;
    int unknownFieldD0;
    int dirty_flags;
    char _padd8[0x218 - 0xd8];
    int unknownField218;
    int unknownField21C;
    int unknownField220;
    int unknownField224;
    int unknownField228;
    int unknownField22C;
    int unknownField230;
    int unknownField234;
    int unknownField238;
} graphics_state;

extern char projection_matrix[];
extern char view_matrix[];
extern char rotation_matrix[];

void func_020190b0(void) {
    graphics_state.unknownField00 = 0x17101610;
    graphics_state.unknownField04 = 0;
    graphics_state.unknownField48 = 2;
    graphics_state.unknownField7C = 0x60293130;
    graphics_state.unknownField90 = 0x002a1b19;
    MTX_Identity43_(&view_matrix);
    MTX_Identity44_(&projection_matrix);
    graphics_state.unknownField80 = 0x4210c210;
    graphics_state.unknownField84 = 0x4210c210;
    graphics_state.unknownField88 = 0x001f008f;
    graphics_state.unknownField8C = (int)0xbfff0000;
    graphics_state.translation_x = 0;
    graphics_state.translation_y = 0;
    graphics_state.translation_z = 0;
    MTX_Identity33_(&rotation_matrix);
    graphics_state.scale_x = 0x1000;
    graphics_state.scale_y = 0x1000;
    graphics_state.scale_z = 0x1000;
    graphics_state.unknownFieldD0 = 0;
    graphics_state.dirty_flags = 0;
    graphics_state.unknownField220 = 0;
    graphics_state.unknownField21C = 0;
    graphics_state.unknownField218 = 0;
    graphics_state.unknownField22C = 0;
    graphics_state.unknownField224 = 0;
    graphics_state.unknownField228 = 0x1000;
    graphics_state.unknownField234 = 0;
    graphics_state.unknownField230 = 0;
    graphics_state.unknownField238 = -0x1000;
}
