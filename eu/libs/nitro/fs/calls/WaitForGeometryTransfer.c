/* Historical directory retained for build configuration; this is a GX DMA wait. */
extern volatile int data_027e00ac;

void WaitForGeometryTransfer(void)
{
    while (data_027e00ac != 0) {}
}
