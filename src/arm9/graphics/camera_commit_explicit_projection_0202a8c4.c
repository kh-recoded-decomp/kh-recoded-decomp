typedef struct { int x, y, z; } VecFx32;

typedef struct {
    char    _0[0xc];
    int     nearClip;
    int     farClip;
    VecFx32 target;
    VecFx32 pos;
    VecFx32 up;
} CamActor;

extern struct { char _p00[0xd4]; int flags; } data_0205a924;
extern char    data_0205a92c[];
extern VecFx32 data_0205ab3c;
extern VecFx32 data_0205ab48;
extern VecFx32 data_0205ab54;
extern char    data_0205a970[];

extern void func_02005f10(int top, int bottom, int left, int right, int nearClip, int farClip, int scaleW, void *projectionOut);
extern void func_01ff9b70(const VecFx32 *pos, const VecFx32 *up, const VecFx32 *target, void *viewOut);

void camera_commit_explicit_projection_0202a8c4(CamActor *camera, int projectionTop, int projectionBottom, int projectionLeft, int projectionRight)
{
    func_02005f10(projectionTop, projectionBottom, projectionLeft, projectionRight, camera->nearClip, camera->farClip, 0x1000, data_0205a92c);
    data_0205a924.flags &= ~0x50;
    data_0205ab3c = camera->pos;
    data_0205ab48 = camera->up;
    data_0205ab54 = camera->target;
    func_01ff9b70(&camera->pos, &camera->up, &camera->target, data_0205a970);
    data_0205a924.flags &= ~0xe8;
}
