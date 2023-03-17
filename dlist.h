#ifndef EDA_DLIST_H
#define EDA_DLIST_H

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/// Estrutura de dados: "Node"
typedef struct node {
    void *data;
    struct node *next;
    struct node *prev;
} Node;


/// "métodos" e informações relevantes de uma lista devem estar aqui,
/// as funções são estáticas e embutidas, então isso é crítico para o seu uso fora
/// os respectivos arquivos.
typedef struct llist {
    Node *head;
    Node *tail;
    size_t len;
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

#endif
