typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOverlay060Object_02056f5c(void);
extern void SetOverlayObjectFactory_02008d9c(OverlayObjectFactory factory);
void func_02008f1c(void)
{
    SetOverlayObjectFactory_02008d9c(CreateOverlay060Object_02056f5c);
}
