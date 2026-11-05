typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOv054Actor(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void RegisterOverlay054ActorFactory(void)
{
    SetOverlayObjectFactory(CreateOv054Actor);
}
