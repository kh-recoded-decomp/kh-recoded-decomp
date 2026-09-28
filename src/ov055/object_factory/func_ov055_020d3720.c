typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOverlay060Object_020d3db4(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void func_ov055_020d3720(void)
{
    SetOverlayObjectFactory(CreateOverlay060Object_020d3db4);
}
