//
// Created by jp on 15-03-2023.
//

#ifndef EDA_DLIST_H
#define EDA_DLIST_H

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/// This code will be computational intensive when reading, so a Node
/// with two entries justifies the cost in memory.
typedef struct node {
    void *data;
    struct node *next;
    struct node *prev;
} Node;

/// Associated "methods" and relevant information of a List should be here,
/// functions are static and inlined so this is critical for their use outside
/// the respective files.
typedef struct llist {
    Node *head;
    Node *tail;
    size_t len;
    // fn's pointers.
    Node *(*new_node)(void *);
    Node *(*find_node)(struct llist *, size_t);
    void *(*get)(struct llist *, size_t);
    void *(*get_head)(struct llist *);
    void *(*get_tail)(struct llist *);
    int (*add)(struct llist *, void *, size_t);
    void *(*rm)(struct llist *, size_t);
    void *(*set)(struct llist *, void *, size_t);
    void (*push)(struct llist *, void *);
    void (*push_t)(struct llist *, void *);
    void *(*pop)(struct llist *);
    void *(*pop_t)(struct llist *);
    void (*iter_fn)(struct llist *, void (*fn)(void *));
    void (*iter_t_fn)(struct llist *, void (*fn)(void *));
    void (*reset)(struct llist *);
    void (*destroy)(struct llist *);
} Llist;

Llist *lst_init();

#endif //EDA_DLIST_H
