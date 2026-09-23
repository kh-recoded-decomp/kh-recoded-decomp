/* Fills a typed message with an ID and two values, then sends it to a queue. Evidence: Source implementation directly performs the described operations; see src/calls/func_0201f70c.c. Uncertainty: No material uncertainty for the stated operation; game-specific use may depend on callers. Recovered from Days source src/calls/func_0201f70c.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern void *func_0202b810(void);
extern void OS_SendMessage(void *queue, void *message, int flags);

extern int message_queue;

typedef struct {
    char _0[4];
    int type;
    unsigned short message_id;
    char _a[2];
    int message_argument_1;
    int message_argument_2;
} QueuedMessage;

void QueueTypedMessage_0202ca88(unsigned short message_id, int message_argument_1, int message_argument_2)
{
    QueuedMessage *queued_entry = func_0202b810();

    if (queued_entry == 0)
        return;

    queued_entry->type = 2;
    queued_entry->message_id = message_id;
    queued_entry->message_argument_1 = message_argument_1;
    queued_entry->message_argument_2 = message_argument_2;
    OS_SendMessage(&message_queue, queued_entry, 1);
}
