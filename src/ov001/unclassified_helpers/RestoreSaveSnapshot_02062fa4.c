#include "nitro/types.h"

typedef struct NibblePair {
    u8 low : 4;
    u8 high : 4;
} NibblePair;

typedef struct SaveSection {
    u8 header[0x3c];
    u32 unk_3C;
    u32 unk_40;
    u32 unk_44;
    u32 unk_48;
    s8 unk_4C;
    s8 unk_4D;
    u8 unk_4E;
    NibblePair nibbles;
    u8 body[0xe88];
} SaveSection;

typedef struct SaveBits {
    u8 core[0xc00];
    u8 pad_0c00[0x2888 - 0xc00];
    SaveSection section;
} SaveBits;

typedef struct SaveSnapshot {
    u8 core[0xc00];
    u8 header[0x3c];
    u32 unk_C3C;
    u32 unk_C40;
    u32 unk_C44;
    s8 unk_C48;
    s8 unk_C49;
    u8 unk_C4A;
    NibblePair nibbles;
    u8 body[0xe88];
    u8 difficultyPreset[0x1e0];
} SaveSnapshot;

typedef struct Session {
    u8 pad_0000[0x28];
    u8 difficultyPreset[0x1e0];
} Session;

extern SaveBits *g_saveBits_0205fe0c;
extern Session *data_ov001_020a0460;
extern void func_01ff878c(const void *src, void *dst, u32 size);
extern void func_01ff869c(const void *src, void *dst, u32 size);
extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern void WriteSessionPackedBits_0206459c(int bitOffset, u32 bitCount, u32 value);

void RestoreSaveSnapshot_02062fa4(const SaveSnapshot *snapshot) {
    u32 preset = ReadSessionPackedBits_02064574(0x1a00, 2);
    func_01ff878c(snapshot->core, g_saveBits_0205fe0c->core, 0xc00);
    func_01ff869c(snapshot->header, g_saveBits_0205fe0c->section.header, 0x3c);
    g_saveBits_0205fe0c->section.unk_3C = snapshot->unk_C3C;
    g_saveBits_0205fe0c->section.unk_44 = snapshot->unk_C40;
    g_saveBits_0205fe0c->section.unk_48 = snapshot->unk_C44;
    g_saveBits_0205fe0c->section.unk_4C = snapshot->unk_C48;
    g_saveBits_0205fe0c->section.unk_4D = snapshot->unk_C49;
    g_saveBits_0205fe0c->section.unk_4E = snapshot->unk_C4A;
    g_saveBits_0205fe0c->section.nibbles.low = snapshot->nibbles.low;
    g_saveBits_0205fe0c->section.nibbles.high = snapshot->nibbles.high;
    func_01ff878c(snapshot->body, g_saveBits_0205fe0c->section.body, 0xe88);
    if (preset == 3) {
        func_01ff878c(snapshot->difficultyPreset, data_ov001_020a0460->difficultyPreset, 0x1e0);
    }
    WriteSessionPackedBits_0206459c(0x1a00, 2, preset);
}
