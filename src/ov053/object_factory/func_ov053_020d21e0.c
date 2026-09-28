typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOverlay060Object_020d2b20(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void func_ov053_020d21e0(void)
{
    SetOverlayObjectFactory(CreateOverlay060Object_020d2b20);
}
