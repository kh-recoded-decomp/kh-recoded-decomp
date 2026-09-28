typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOverlay060Object_02013b94(void);
extern void SetOverlayObjectFactory_02013bac(OverlayObjectFactory factory);
void func_02013b98(void)
{
    SetOverlayObjectFactory_02013bac(CreateOverlay060Object_02013b94);
}
