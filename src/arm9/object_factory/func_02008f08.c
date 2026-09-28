typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOverlay060Object_02056f5a(void);
extern void SetOverlayObjectFactory_02008d9c(OverlayObjectFactory factory);
void func_02008f08(void)
{
    SetOverlayObjectFactory_02008d9c(CreateOverlay060Object_02056f5a);
}
