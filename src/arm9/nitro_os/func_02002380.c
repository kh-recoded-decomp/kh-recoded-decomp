typedef unsigned short u16;

#define REG_EXMEM_CNT (*(volatile u16 *)0x04000204)

void OSi_FreeCardBus(void)
{
    REG_EXMEM_CNT |= 0x0800;
}
