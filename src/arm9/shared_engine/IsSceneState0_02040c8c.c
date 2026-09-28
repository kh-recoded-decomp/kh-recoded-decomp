extern int Game_PollSceneAlive(void);
int IsSceneState0_02040c8c(void)
{
    return Game_PollSceneAlive() == 0;
}
