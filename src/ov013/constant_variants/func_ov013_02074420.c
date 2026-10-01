extern unsigned int _data_ov015_02074ce0;
extern unsigned int PlaySoundEffect_0204d924();

void func_ov013_02074420(int context)

{
  int previousSelection;

  previousSelection = *(int *)(_data_ov015_02074ce0 + 16);
  *(unsigned int *)(_data_ov015_02074ce0 + 16) = *(unsigned int *)(context + 0xc);
  if (*(int *)(_data_ov015_02074ce0 + 16) == previousSelection) {
    return;
  }
  PlaySoundEffect_0204d924(2,0);
  return;
}
