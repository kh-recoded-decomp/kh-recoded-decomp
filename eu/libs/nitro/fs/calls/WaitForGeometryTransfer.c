/* Historical directory retained for build configuration; this is a GX DMA wait. */
extern volatile int gGeometryTransferBusy;

void WaitForGeometryTransfer(void)
{
    while (gGeometryTransferBusy != 0) {}
}
