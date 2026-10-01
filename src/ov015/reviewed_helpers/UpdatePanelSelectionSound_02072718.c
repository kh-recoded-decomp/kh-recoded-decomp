extern unsigned int _data_ov015_0207e960;
extern unsigned int PlaySoundEffect_0204d924();

void UpdatePanelSelectionSound_02072718(int context)

{
  int previousSelection;
  
  previousSelection = *(int *)(_data_ov015_0207e960 + 200);
  *(unsigned int *)(_data_ov015_0207e960 + 200) = *(unsigned int *)(context + 0xc);
  if (*(int *)(_data_ov015_0207e960 + 200) == previousSelection) {
    return;
  }
  PlaySoundEffect_0204d924(2,0);
  return;
}
