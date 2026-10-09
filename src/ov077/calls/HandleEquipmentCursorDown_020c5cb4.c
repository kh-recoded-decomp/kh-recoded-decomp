typedef struct EquipmentMenuState {
    unsigned char pad_0000[0x18];
    int transitionState;
    unsigned char pad_001c[0x7fb0 - 0x1c];
    int interactionState;
} EquipmentMenuState;

void HandleEquipmentCursorDown_020c5cb4(EquipmentMenuState *menu)
{
    if (menu->transitionState == 0 && menu->interactionState == 4) {
        return;
    }
}
