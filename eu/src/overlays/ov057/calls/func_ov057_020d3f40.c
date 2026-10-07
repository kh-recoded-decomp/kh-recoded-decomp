typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOverlay057Entity(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void func_ov057_020d3f40(void)
{
    SetOverlayObjectFactory(CreateOverlay057Entity);
}
