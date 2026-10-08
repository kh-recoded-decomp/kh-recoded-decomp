typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOv053Actor(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void func_ov053_020d2200(void)
{
    SetOverlayObjectFactory(CreateOv053Actor);
}
