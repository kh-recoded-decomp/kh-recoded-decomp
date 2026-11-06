extern unsigned int gOv013PanelGlobals;
extern unsigned int PlaySoundEffect();

void SetOv013WidgetSelectionAWithSound(int context)

{
  int previousSelection;

  previousSelection = *(int *)(gOv013PanelGlobals + 16);
  *(unsigned int *)(gOv013PanelGlobals + 16) = *(unsigned int *)(context + 0xc);
  if (*(int *)(gOv013PanelGlobals + 16) == previousSelection) {
    return;
  }
  PlaySoundEffect(2,0);
  return;
}
