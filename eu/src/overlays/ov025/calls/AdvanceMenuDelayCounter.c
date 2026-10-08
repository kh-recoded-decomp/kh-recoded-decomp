extern unsigned int SetPanelSessionActive();

void AdvanceMenuDelayCounter(int menu)

{
  *(unsigned char *)(menu + 0x64e8) = *(unsigned char *)(menu + 0x64e8) + '\x01';
  if ((3 <= *(unsigned char *)(menu + 0x64e8)) &&
     (SetPanelSessionActive(), *(unsigned char *)(menu + 0x64e9) != '\0')) {
    *(unsigned char *)(menu + 0x64ea) = 2;
  }
  return;
}
