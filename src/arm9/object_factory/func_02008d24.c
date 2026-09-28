typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOverlay060Object_02056f50(void);
extern void SetOverlayObjectFactory_02008ca4(OverlayObjectFactory factory);
void func_02008d24(void)
{
    SetOverlayObjectFactory_02008ca4(CreateOverlay060Object_02056f50);
}
