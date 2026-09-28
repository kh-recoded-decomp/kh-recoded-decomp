void relocateFontResource_02018314(int resourceBase) {
    unsigned int *sectionWords = (unsigned int *)(resourceBase + *(unsigned short *)(resourceBase + 0xc));
    int sectionIndex = 0;
    if (sectionIndex < (int)(unsigned int)*(unsigned short *)(resourceBase + 0xe)) {
        do {
            switch (*sectionWords) {
            case 0x46494e46:
                sectionWords[4] += resourceBase;
                if (sectionWords[5] != 0) sectionWords[5] += resourceBase;
                if (sectionWords[6] != 0) sectionWords[6] += resourceBase;
                break;
            case 0x43574448:
                if (sectionWords[3] != 0) sectionWords[3] += resourceBase;
                break;
            case 0x434d4150:
                if (sectionWords[4] != 0) sectionWords[4] += resourceBase;
                break;
            case 0x43474c50:
                break;
            }
            sectionIndex++;
            sectionWords = (unsigned int *)((int)sectionWords + sectionWords[1]);
        } while (sectionIndex < (int)(unsigned int)*(unsigned short *)(resourceBase + 0xe));
    }
}
