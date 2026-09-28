/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern void FSi_WaitForCardThread(int, int);
extern void FS_UnloadOverlay(int, int);

void func_02029f98(int processor, int overlay_id)
{
    FSi_WaitForCardThread(processor, overlay_id);
    FS_UnloadOverlay(processor, overlay_id);
}
