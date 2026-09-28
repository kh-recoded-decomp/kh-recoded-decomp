extern int Game_PollSceneAlive(void);
int IsSceneState0_020bdd94(void)
{
    return Game_PollSceneAlive() == 0;
}
