typedef struct { int identity_matrix[3][3]; } MtxFx33;

extern void MTX_Identity33_(MtxFx33 *mtx);
extern void func_01ff80e4(void);
extern void func_01ffa37c(unsigned int cmd, const void *src, unsigned int words);
extern void func_02019188(void);

typedef struct {
    char pad_00[0xb8];
    int translation_x;
    int translation_y;
    int translation_z;
    int scale_x;
    int scale_y;
    int scale_z;
    char pad_d0[0x4];
    unsigned int dirty_flags;
} GraphicsState;

extern GraphicsState graphics_state;
extern MtxFx33  rotation_matrix;

void ResetGraphicsTransform_0202fdf4(void) {
    MtxFx33 identity_matrix;
    int graphics_command;

    graphics_state.scale_z = 0x1000;
    graphics_state.scale_y = 0x1000;
    graphics_state.scale_x = 0x1000;
    MTX_Identity33_(&identity_matrix);
    MTX_Identity33_(&rotation_matrix);
    graphics_state.translation_z = 0;
    graphics_state.translation_y = 0;
    graphics_state.translation_x = 0;
    graphics_state.dirty_flags &= ~0xa4u;
    func_02019188();
    graphics_command = 0x7fff;
    func_01ffa37c(0x20, &graphics_command, 1);
    func_01ff80e4();
}
