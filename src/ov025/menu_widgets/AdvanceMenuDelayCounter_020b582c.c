extern unsigned int func_ov001_0207b4d8();

void AdvanceMenuDelayCounter_020b582c(int menu)

{
  *(unsigned char *)(menu + 0x64e8) = *(unsigned char *)(menu + 0x64e8) + '\x01';
  if ((3 <= *(unsigned char *)(menu + 0x64e8)) &&
     (func_ov001_0207b4d8(), *(unsigned char *)(menu + 0x64e9) != '\0')) {
    *(unsigned char *)(menu + 0x64ea) = 2;
  }
  return;
}
