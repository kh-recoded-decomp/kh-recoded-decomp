typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOverlay060Object_02056f4c(void);
extern void SetOverlayObjectFactory_02008d9c(OverlayObjectFactory factory);
void func_02008e70(void)
{
    SetOverlayObjectFactory_02008d9c(CreateOverlay060Object_02056f4c);
}
