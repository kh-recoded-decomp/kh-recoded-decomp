extern int Game_PollSceneAlive(void);
int IsSceneState0_020655c4(void)
{
    return Game_PollSceneAlive() == 0;
}
