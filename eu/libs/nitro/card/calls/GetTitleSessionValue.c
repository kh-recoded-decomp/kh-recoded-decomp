/* Returns word 0 of the title-session record; its role is separate from status at +4. */

extern int *data_ov000_02063a08;

int GetTitleSessionValue(void) {
    return *data_ov000_02063a08;
}
