typedef struct { int x, y, z; } VecFx32;

typedef struct {
    int     perspectiveParams[4];
    int     farClip;
    VecFx32 target;
    VecFx32 pos;
    VecFx32 up;
} CamActor;

extern struct {
    char    _p00[0xd4];
    int     flags;
    char    _pd8[0x218-0xd8];
    VecFx32 cachePos;
    VecFx32 cacheUp;
    VecFx32 cacheTarget;
} data_0205a924;

extern char data_0205a92c[];
extern char data_0205a970[];

extern void func_02005dc4(int fovySin, int fovyCos, int aspect, int nearClip, int farClip, int scaleW, void *projectionOut);
extern void func_01ff9b70(const VecFx32 *pos, const VecFx32 *up, const VecFx32 *target,
                          void *viewOut);

void camera_commit_projection_0202a814(CamActor *camera)
{
    func_02005dc4(camera->perspectiveParams[0], camera->perspectiveParams[1], camera->perspectiveParams[2],
                  camera->perspectiveParams[3], camera->farClip, 0x1000, data_0205a92c);
    data_0205a924.flags &= ~0x50;
    data_0205a924.cachePos = camera->pos;
    data_0205a924.cacheUp = camera->up;
    data_0205a924.cacheTarget = camera->target;
    func_01ff9b70(&camera->pos, &camera->up, &camera->target, data_0205a970);
    data_0205a924.flags &= ~0xe8;
}
