extern int PXI_SendWordByFifo(int a, int b, int c);

void PMi_SendPxiData_0201060c(int arg0)
{
    while (PXI_SendWordByFifo(8, arg0, 0) != 0);
}
