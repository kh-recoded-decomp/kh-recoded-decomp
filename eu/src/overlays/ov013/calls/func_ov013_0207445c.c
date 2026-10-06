extern unsigned int data_ov013_02074ce0;
extern unsigned int PlaySoundEffect();

void func_ov013_0207445c(int context)

{
  int previousSelection;

  previousSelection = *(int *)(data_ov013_02074ce0 + 20);
  *(unsigned int *)(data_ov013_02074ce0 + 20) = *(unsigned int *)(context + 0xc);
  if (*(int *)(data_ov013_02074ce0 + 20) == previousSelection) {
    return;
  }
  PlaySoundEffect(2,0);
  return;
}
