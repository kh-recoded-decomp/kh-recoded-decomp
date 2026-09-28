extern void Ov008_RaiseSelectedItemWidget(void);
extern void Ov008_RegisterSlotCells(void);
extern void Ov008_DrawMenuPageTexts(void);
void RefreshMenuPage_02088548(void)
{
    Ov008_RaiseSelectedItemWidget();
    Ov008_RegisterSlotCells();
    Ov008_DrawMenuPageTexts();
}
