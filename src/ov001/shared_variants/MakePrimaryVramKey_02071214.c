typedef struct {
    char pad0000[108];
    unsigned int nPrimaryBase;
    unsigned int nSecondaryBase;
} Ov002VramLayout;

typedef struct {
    char pad0000[4];
    Ov002VramLayout *pLayout;
} Ov002VramRoot;

extern Ov002VramRoot data_020a04a4;

unsigned int MakePrimaryVramKey_02071214(unsigned int slot) {
    unsigned int base = data_020a04a4.pLayout->nPrimaryBase + 0x8000;

    return ((base & 0xfffffc) << 7) | 0x80000000 | (slot & 0x1ff);
}
