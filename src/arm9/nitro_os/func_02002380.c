/* CC0 source: Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/os/auto/OSi_FreeCardBus.c. */
typedef unsigned short u16;

/* External memory control. Bit 11 holds the NDS-slot access rights: 0 gives the
   card bus to the ARM9, 1 to the ARM7. */
#define REG_EXMEM_CNT (*(volatile u16 *)0x04000204)

void OSi_FreeCardBus(void)
{
    REG_EXMEM_CNT |= 0x0800;
}
