#include "nitro/types.h"

typedef struct {
    u32 words[4];
} Block16;

typedef struct {
    Block16 header;
    u8 ownName[0x16];
    u8 otherName[0x16];
    u8 pad3c[0x22];
    u8 macAddress[6];
    u8 budgetFlag;
    u8 modeFlag;
    u8 pad66;
    s8 field67;
    s8 field68;
    u8 pad69[2];
    u8 field6b;
    u8 padEnd[4];
} PlayerCard;

extern void func_01ff8830(void *dst, int val, unsigned int n);
extern void ReadMacAddress_02004ac8(u8 *address);
extern s8 *g_context_0207e960;
extern int func_ov002_02066c78(int a, int b, int c, int d);
extern int func_02027348(int a, int b);
extern Block16 *func_ov002_02066fc8(void);
extern u32 func_ov002_02061930(void);
extern u32 func_ov002_0206193c(void);
extern void func_ov002_02066394(void *dst, u32 value);

void InitPlayerCard_0206f524(PlayerCard *card)
{
    u32 nameId;

    func_01ff8830(card, 0, 0x70);
    ReadMacAddress_02004ac8(card->macAddress);
    card->field68 = g_context_0207e960[2];
    card->field67 = g_context_0207e960[3];
    card->budgetFlag = (u8)func_ov002_02066c78(5, 0, 0, 0);
    card->modeFlag = (u8)func_ov002_02066c78(6, 0, 0, 0);
    card->field6b = (u8)func_02027348(0xf38, 4);
    card->header = *func_ov002_02066fc8();
    nameId = func_ov002_02061930();
    func_ov002_02066394(card->ownName, nameId);
    nameId = func_ov002_0206193c();
    func_ov002_02066394(card->otherName, nameId);
}
