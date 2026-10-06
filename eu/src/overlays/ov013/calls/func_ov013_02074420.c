extern unsigned int data_ov013_02074ce0;
extern unsigned int PlaySoundEffect();

void func_ov013_02074420(int context)

{
  int previousSelection;

  previousSelection = *(int *)(data_ov013_02074ce0 + 16);
  *(unsigned int *)(data_ov013_02074ce0 + 16) = *(unsigned int *)(context + 0xc);
  if (*(int *)(data_ov013_02074ce0 + 16) == previousSelection) {
    return;
  }
  PlaySoundEffect(2,0);
  return;
}
