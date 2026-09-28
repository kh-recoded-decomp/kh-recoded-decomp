extern int Game_PollSceneAlive(void);
int IsSceneState0_020be7c0(void)
{
    return Game_PollSceneAlive() == 0;
}
