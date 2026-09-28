typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOverlay060Object_020c7a48(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void func_ov059_020c7460(void)
{
    SetOverlayObjectFactory(CreateOverlay060Object_020c7a48);
}
