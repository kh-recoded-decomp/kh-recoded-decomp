typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOverlay055Entity(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void func_ov055_020d3740(void)
{
    SetOverlayObjectFactory(CreateOverlay055Entity);
}
