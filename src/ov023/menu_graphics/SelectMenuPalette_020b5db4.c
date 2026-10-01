extern unsigned int data_ov023_020b6eec;
extern unsigned int GXS_LoadOBJPltt_0200736c();

void SelectMenuPalette_020b5db4(int menu,int palette)

{
  if ((1 <= palette) && (palette <= 4)) {
    GXS_LoadOBJPltt_0200736c((unsigned char *)&data_ov023_020b6eec + (palette + -1) * 8,2,8);
    *(int *)(menu + 0x6870) = palette;
  }
  return;
}
