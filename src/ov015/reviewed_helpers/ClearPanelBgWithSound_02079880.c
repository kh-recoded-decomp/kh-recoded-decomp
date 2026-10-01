extern unsigned int ClearBuffer2048_02078f00();
extern unsigned int G2S_GetBG2ScrPtr_02006f0c();
extern unsigned int PlaySoundEffect_0204d924();

void ClearPanelBgWithSound_02079880(void)

{
  void *dst;
  
  PlaySoundEffect_0204d924(2,1);
  dst = G2S_GetBG2ScrPtr_02006f0c();
  ClearBuffer2048_02078f00(dst);
  return;
}
