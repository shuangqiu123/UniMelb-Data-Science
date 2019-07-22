/* pqueue.h */
struct pqueue;

/* Creates an empty priority queue. */
struct pqueue *makeQueue();

/* Adds an item to a priority queue. */
void enqueue(struct pqueue *queue, int priority, void *data);

/* Takes the highest priority item from the queue. */
void *dequeue(struct pqueue *queue);

/* Updates the position of the given data item. 
    Note: if you were writing this generally, you
    might like to include a priority data update 
    function in your pqueue creation (like the
    hash table exercise) that allows you to read
    and update priority information and set and
    retrieve heap position information from
    an auxillary data structure (there's a lot
    of options here which are all fairly reasonable
    choices).
    For now, presume this does nothing (or make it 
    read through the array and update priorities,
    it depends on your dequeue implementation). */
void update(struct pqueue *queue, int index);

/* Returns 1 if the queue is empty, 0 otherwise. */
int empty(struct pqueue *queue);

/* Frees all memory allocated by the queue given. */
void freeQueue(struct pqueue *queue);