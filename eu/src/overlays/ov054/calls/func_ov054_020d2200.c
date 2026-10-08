typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOv054Actor(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void func_ov054_020d2200(void)
{
    SetOverlayObjectFactory(CreateOv054Actor);
}
