typedef struct {
    char bytes[0x18];
} FrameTextureEntry;

typedef struct {
    char pad0000[8];
    FrameTextureEntry *frameTextureSlots[5];
} FrameTextureManager;

extern FrameTextureEntry data_02055c78[];
extern FrameTextureManager data_02055c5c;

void set_frame_texture_vram_slot_order_020137b0(int slot0Index, int slot1Index, int slot2Index, int slot3Index, int slot4Index) {
    data_02055c5c.frameTextureSlots[0] = &data_02055c78[slot0Index];
    data_02055c5c.frameTextureSlots[1] = &data_02055c78[slot1Index];
    data_02055c5c.frameTextureSlots[2] = &data_02055c78[slot2Index];
    data_02055c5c.frameTextureSlots[3] = &data_02055c78[slot3Index];
    data_02055c5c.frameTextureSlots[4] = &data_02055c78[slot4Index];
}
