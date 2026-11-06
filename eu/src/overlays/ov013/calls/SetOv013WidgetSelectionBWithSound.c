extern unsigned int gOv013PanelGlobals;
extern unsigned int PlaySoundEffect();

void SetOv013WidgetSelectionBWithSound(int context)

{
  int previousSelection;

  previousSelection = *(int *)(gOv013PanelGlobals + 20);
  *(unsigned int *)(gOv013PanelGlobals + 20) = *(unsigned int *)(context + 0xc);
  if (*(int *)(gOv013PanelGlobals + 20) == previousSelection) {
    return;
  }
  PlaySoundEffect(2,0);
  return;
}
