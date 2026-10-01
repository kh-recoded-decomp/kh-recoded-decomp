extern unsigned int _data_ov002_0206c464;
extern unsigned int PlaySoundEffect_0204d924();

void UpdateMenuSelectionSound_02065d54(int context)

{
  int previousSelection;
  
  previousSelection = *(int *)(_data_ov002_0206c464 + 0xc);
  *(unsigned int *)(_data_ov002_0206c464 + 0xc) = *(unsigned int *)(context + 0xc);
  if (*(int *)(_data_ov002_0206c464 + 0xc) == previousSelection) {
    return;
  }
  PlaySoundEffect_0204d924(2,0);
  return;
}
