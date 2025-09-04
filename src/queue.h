#ifndef DS_Q_H_
#define DS_Q_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DS_Queue DS_Queue;
static inline DS_Queue *ds_q_create();
static inline size_t ds_q_free(DS_Queue *queue);

static inline

#ifdef __cplusplus
}
#endif

// #ifdef DS_Q_IMPLEMENTATION

struct DS_Queue {
    Node *head;
    Node *tail;
    size_t size;
};

#endif // DS_Q_IMPLEMENTATION
#endif // DS_Q_H_
