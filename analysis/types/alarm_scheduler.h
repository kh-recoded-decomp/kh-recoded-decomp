/* ARM9 alarm records use four-byte alignment, including 64-bit tick fields. */
typedef struct AlarmTickWords {
    unsigned int low;
    unsigned int high;
} AlarmTickWords;

typedef void (*AlarmCallback)(void *argument);
typedef struct AlarmRecord AlarmRecord;
struct AlarmRecord {
    AlarmCallback handler;       /* 0x00 */
    void *argument;              /* 0x04 */
    unsigned int tag;            /* 0x08 */
    AlarmTickWords fire;         /* 0x0c */
    AlarmRecord *previous;       /* 0x14 */
    AlarmRecord *next;           /* 0x18 */
    AlarmTickWords period;       /* 0x1c */
    AlarmTickWords start;        /* 0x24 */
};

typedef struct AlarmSchedulerState {
    unsigned short active;      /* 0x00 */
    unsigned short padding;     /* 0x02 */
    AlarmRecord *head;           /* 0x04 */
    AlarmRecord *tail;           /* 0x08 */
} AlarmSchedulerState;
