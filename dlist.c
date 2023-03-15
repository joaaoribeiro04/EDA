//
// Created by jp on 15-03-2023.
//

#include "dlist.h"

/// Initialize a new node.
static inline Node *new_node(void *data) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = data;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

/// Find a node and the best way to iterate over it.
static inline Node *find_node(Llist *l, size_t pos) {
    if (pos > l->len) {
        return NULL;
    }
    Node *iter;
    size_t currPos;
    size_t reverse;
    /// check the best to way to iterate, head or tail.
    if (pos > ((l->len - 1) / 2)) {
        reverse = 1;
        currPos = l->len - 1;
        iter = l->tail;
    } else {
        reverse = 0;
        currPos = 0;
        iter = l->head;
    }
    while (iter != NULL) {
        if (currPos == pos) {
            break;
        }
        iter = (reverse ? (iter->prev) : (iter->next));
        currPos = (reverse ? (currPos - 1) : (currPos + 1));
    }
    return iter;
}

/// Get and element(*ptr->data) in an arbitrary position.
static inline void *get(Llist *l, size_t pos) {
    Node *n = find_node(l, pos);
    return n == NULL ? n : n->data;
}

/// Get the head(*ptr->data) of the list.
static inline void *get_head(Llist *l) {
    return l->head == NULL ? NULL : l->head->data;
}

/// Get the tail(*ptr->data) of the list.
static inline void *get_tail(Llist *l) {
    return l->head == NULL ? NULL : l->tail->data;
}

/// Add and element(*ptr->data) in an arbitrary position.
static inline int add(Llist *l, void *data, size_t pos) {
    if (pos > l->len) {
        return -1;
    }
    Node *newNode;
    Node *iter;
    newNode = new_node(data);
    /// Check if list is empty.
    if (l->len == 0) {
        l->head = newNode;
        l->tail = newNode;
        l->len++;
        return 0;
    }
    iter = find_node(l, pos);
    if (iter != NULL) {
        newNode->prev = iter->prev;
        newNode->next = iter;
        if (iter->prev == NULL) {
            l->head = newNode;
        } else {
            iter->prev->next = newNode;
        }
        iter->prev = newNode;
    } else {
        /// Add at the end
        l->tail->next = newNode;
        newNode->prev = l->tail;
        l->tail = newNode;
    }
    l->len++;
    return 0;
}

/// Change and element(*ptr->data) in an arbitrary position.
static inline void *set(Llist *l, void *data, size_t pos) {
    Node *currNode = find_node(l, pos);
    if (currNode == NULL) {
        return NULL;
    }
    void *oldData = currNode->data;
    currNode->data = data;

    return oldData;
}

/// Insert an element to the head.
static inline void push(Llist *l, void *data) {
    Node *newNode = new_node(data);

    // if list is empty
    if (l->len == 0) {
        l->tail = newNode;
    } else {
        // if there is at least one element
        l->head->prev = newNode;
        newNode->next = l->head;
    }
    l->head = newNode;
    l->len++;
}

/// Insert an element to the tail.
static inline void push_t(Llist *l, void *data) {
    Node *newNode = new_node(data);

    // if list is empty
    if (l->len == 0) {
        l->head = newNode;
    } else {
        // if there is at least one element
        l->tail->next = newNode;
        newNode->prev = l->tail;
    }
    l->tail = newNode;
    l->len++;
}

/// Remove and element in an arbitrary position.
static inline void *rm(Llist *l, size_t pos) {
    Node *currNode = find_node(l, pos);
    void *data = NULL;

    if (currNode == NULL) {
        return NULL;
    }
    data = currNode->data;
    if (currNode->prev == NULL) {
        l->head = currNode->next;
    } else {
        currNode->prev->next = currNode->next;
    }
    if (currNode->next == NULL) {
        l->tail = currNode->prev;
    } else {
        currNode->next->prev = currNode->prev;
    }
    l->len--;
    free(currNode);

    return data;
}

/// Remove a element (list->head);
static inline void *pop(Llist *l) {
    if (!l) {
        return NULL;
    }
    Node *n = l->head;
    if (n == NULL) {
        return NULL;
    }
    void *data = n->data;
    if (rm(l, 0) == NULL) {
        return NULL;
    }
    return data;
}

/// Remove a element (list->tail);
static inline void *pop_t(Llist *l) {
    Node *n = l->tail;
    if (n == NULL) {
        return NULL;
    }
    void *data = n->data;
    if (rm(l, (l->len - 1)) == NULL) {
        return NULL;
    }
    return data;
}

/// Iterates over the entire list from the beginning and
/// calls the specified function with with each element.
static inline void iter_fn(Llist *l, void (*f)(void *)) {
    Node *iter = l->head;

    while (iter != NULL) {
        (*f)(iter->data);
        iter = iter->next;
    }
}

/// Iterates over the entire list from the end and
/// calls the specified function with with each element.
static inline void iter_t_fn(Llist *l, void (*f)(void *)) {
    Node *currNode = l->tail;

    while (currNode != NULL) {
        (*f)(currNode->data);
        currNode = currNode->prev;
    }
}

/// Destroys the list and allocates a new one (empty).
static inline void reset(Llist *l) {
    Node *currNode = l->head;
    Node *nextNode;

    while (currNode != NULL) {
        nextNode = currNode->next;
        free(currNode);
        currNode = nextNode;
    }
    l->head = NULL;
    l->tail = NULL;
    l->len = 0;
}

/// Destroys a list and frees all list's related memory.
/// Sometimes iter_fn may be better if additional frees are required.
static inline void destroy(Llist *l) {
    Node *currNode = l->head;
    Node *nextNode;

    while (currNode != NULL) {
        nextNode = currNode->next;
        free(currNode);
        currNode = nextNode;
    }
    free(l);
}

/// Initialize a new list, with all the info nedeed.
Llist *lst_init() {
    Llist *l = (Llist *)malloc(sizeof(Llist));
    l->len = 0;
    l->head = NULL;
    l->tail = NULL;
    l->new_node = &new_node;
    l->find_node = &find_node;
    l->get = &get;
    l->get_head = &get_head;
    l->get_tail = &get_tail;
    l->add = &add;
    l->rm = &rm;
    l->set = &set;
    l->push = &push;
    l->push_t = &push_t;
    l->pop = &pop;
    l->pop_t = &pop_t;
    l->iter_fn = &iter_fn;
    l->iter_t_fn = &iter_t_fn;
    l->reset = &reset;
    l->destroy = &destroy;

    return l;
}