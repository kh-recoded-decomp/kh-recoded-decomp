extern int QueryActiveStateOrDelegate();
extern int Ov022_GetEntryField66();
extern int Ov002_PostCrawlScoreLine();

int ScriptCmd_PostCrawlScoreLine_020a06a4(int arg0) {
    Ov002_PostCrawlScoreLine(Ov022_GetEntryField66(QueryActiveStateOrDelegate()));
    return 1;
}
