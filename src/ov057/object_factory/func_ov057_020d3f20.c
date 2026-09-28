typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOverlay060Object_020d428c(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void func_ov057_020d3f20(void)
{
    SetOverlayObjectFactory(CreateOverlay060Object_020d428c);
}
