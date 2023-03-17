#include "dlist.h"

/// Inicia um novo Node.
static inline Node *new_node(void *data) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = data;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

/// Encontrar um Node e a melhor maneira de iterar sobre ele
static inline Node *find_node(Llist *l, size_t pos) {
    if (pos > l->len) {
        return NULL;
    }
    Node *iter;
    size_t currPos;
    size_t reverse;
    /// melhor maneira de iterar cabeça ou calda
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

/// Obtenha um elemento (*ptr->data)
static inline void *get(Llist *l, size_t pos) {
    Node *n = find_node(l, pos);
    return n == NULL ? n : n->data;
}

/// Obtenha a cabeça (*ptr->data) da lista
static inline void *get_head(Llist *l) {
    return l->head == NULL ? NULL : l->head->data;
}

/// Obtenha o final (*ptr->data) da lista
static inline void *get_tail(Llist *l) {
    return l->head == NULL ? NULL : l->tail->data;
}

/// Adiciona um elemento (*ptr->data)
static inline int add(Llist *l, void *data, size_t pos) {
    if (pos > l->len) {
        return -1;
    }
    Node *newNode;
    Node *iter;
    newNode = new_node(data);
    /// Verifica se a lista esta vazia
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
        /// Adicionar no final
        l->tail->next = newNode;
        newNode->prev = l->tail;
        l->tail = newNode;
    }
    l->len++;
    return 0;
}

/// Mudança de um elemento (*ptr->data)
static inline void *set(Llist *l, void *data, size_t pos) {
    Node *currNode = find_node(l, pos);
    if (currNode == NULL) {
        return NULL;
    }
    void *oldData = currNode->data;
    currNode->data = data;

    return oldData;
}

/// Inserir um elemento na cabeça
static inline void push(Llist *l, void *data) {
    Node *newNode = new_node(data);

    /// se a lista estiver vazia
    if (l->len == 0) {
        l->tail = newNode;
    } else {
        /// se houver pelo menos um elemento
        l->head->prev = newNode;
        newNode->next = l->head;
    }
    l->head = newNode;
    l->len++;
}

/// Inserir um elemento na cauda
static inline void push_t(Llist *l, void *data) {
    Node *newNode = new_node(data);

    /// se a lista estiver vazia
    if (l->len == 0) {
        l->head = newNode;
    } else {
        /// se houver pelo menos um elemento
        l->tail->next = newNode;
        newNode->prev = l->tail;
    }
    l->tail = newNode;
    l->len++;
}

/// Remove um elemento
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

/// Remove um elemento (list->head);
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

/// Remove um elemento (list->tail);
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

/// Itera sobre toda a lista desde o início e
/// chama a função especificada com cada elemento.
static inline void iter_fn(Llist *l, void (*f)(void *)) {
    Node *iter = l->head;

    while (iter != NULL) {
        (*f)(iter->data);
        iter = iter->next;
    }
}

/// Itera sobre toda a lista a partir do final e
/// chama a função especificada com cada elemento.
static inline void iter_t_fn(Llist *l, void (*f)(void *)) {
    Node *currNode = l->tail;

    while (currNode != NULL) {
        (*f)(currNode->data);
        currNode = currNode->prev;
    }
}

/// Destrói a lista e aloca uma nova
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


/// Destrói uma lista e liberta toda a memória relacionada à lista.
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

/// Inicia uma nova lista com todas as informações necessarias
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