extern int Game_PollSceneAlive(void);
int IsSceneState0_02065758(void)
{
    return Game_PollSceneAlive() == 0;
}
