/* Reads master-brightness mode/value and returns the signed value represented by the register.
 * The exact public SDK symbol is not established from the body, so the target address-based name is retained; behavior is limited to the implemented operation. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/auto/func_02005760.c.
 * Original routine: func_02005760. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#define REG_GX_MASTER_BRIGHT_E_MOD_SHIFT 14
#define REG_GX_MASTER_BRIGHT_E_MOD_MASK 0xc000
#define REG_GX_MASTER_BRIGHT_E_VALUE_MASK 0x001f



/* func_02006770 -- NitroSDK gx.c: GXx_GetMasterBrightness_. */
int func_02006770 (vu16 *reg)
{
	u16 mode = (u16)(*reg & REG_GX_MASTER_BRIGHT_E_MOD_MASK);

	if (mode == 0) {
		return 0;
	} else if (mode == (1 << REG_GX_MASTER_BRIGHT_E_MOD_SHIFT))   {
		return *reg & REG_GX_MASTER_BRIGHT_E_VALUE_MASK;
	} else if (mode == (2 << REG_GX_MASTER_BRIGHT_E_MOD_SHIFT))   {
		return -(*reg & REG_GX_MASTER_BRIGHT_E_VALUE_MASK);
	} else {
		return 0;
	}
}
