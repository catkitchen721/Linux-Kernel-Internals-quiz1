#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct __node {                   
    int value;
    struct __node *next;
} node_t;

static inline void list_add_node_t(node_t **list, node_t *node_t) 
{
    node_t->next = *list;
    *list = node_t;
}

static inline void list_concat(node_t **left, node_t *right) 
{
    while (*left)
        left = &((*left)->next);  /*LLL*/
    *left = right;
}

void quicksort(node_t **list)
{
    if (!*list)
        return;

    node_t *pivot = *list;
    int value = pivot->value;
    node_t *p = pivot->next;
    pivot->next = NULL;

    node_t *left = NULL, *right = NULL;
    while (p) {
        node_t *n = p;
        p = p->next;
        list_add_node_t(n->value > value ? &right : &left, n);  /*AAA, BBB*/
    }

    quicksort(&left);
    quicksort(&right);

    node_t *result = NULL;
    list_concat(&result, left);
    list_concat(&result, pivot);  /*CCC*/
    list_concat(&result, right);  /*CCC*/
    *list = result;
}

static bool list_is_ordered(node_t *list) {
    bool first = true;
    int value;
    while (list) {
        if (first) {
            value = list->value;
            first = false;
        } else {
            if (list->value < value)
                return false;
            value = list->value;
        }
        list = list->next;
    }
    return true;
}

static void list_display(node_t *list) 
{
    printf("%s IN ORDER : ", list_is_ordered(list) ? "   " : "NOT");
    while (list) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

static node_t *list_make_node_t(node_t *list, int n)
{
    node_t *tmp = (node_t *)malloc(sizeof(node_t));
    tmp->value = n;
    tmp->next = list;
    return tmp;
}

static void list_free(node_t **list)
{
    while (*list) {
        node_t *tmp = *list;
        *list = (*list)->next;
        free(tmp);
    }
}

int main(int argc, char **argv) 
{
    size_t count = 20;

    node_t *list = NULL;
    while (count--)
        list = list_make_node_t(list, random() % 1024);

    list_display(list);
    quicksort(&list);
    list_display(list);

    if (!list_is_ordered(list))
        return EXIT_FAILURE;

    list_free(&list);
    return EXIT_SUCCESS;
}
