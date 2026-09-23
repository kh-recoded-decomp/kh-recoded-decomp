/* Behavior: Prepares a loaded font so the game can find character shapes, widths, and character mappings.
 * Inputs/outputs and evidence: Walks NFTR sections and rebases fields for FINF, CWDH and CMAP blocks; CGLP has no rebased fields.
 * Uncertainty: NFTR section structure is recognizable from tags; malformed input handling is not established.
 * Source: khdays-decomp/src/auto/func_02014874.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
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
