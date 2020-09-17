#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct __node {
    int value;
    struct __node *next;
} node_t;

void add_entry(node_t **head, int new_value)
{
    node_t **indirect = head;

    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = new_value;
    new_node->next = NULL;

    assert(new_node);
    while (*indirect)
        indirect = &(*indirect)->next;
    *indirect = new_node;
}

node_t *find_entry(node_t *head, int value)
{
    node_t *current = head;
    for (; current && current->value != value; current = current->next)
        /* interate */;
    return current;
}

void remove_entry(node_t **head, node_t *entry)
{
    node_t **indirect = head;

    while ((*indirect) != entry)
        indirect = &(*indirect)->next;

    *indirect = entry->next;
    free(entry);
}

node_t *swap_pair(node_t *head)
{
    for (node_t **node = &head; *node && (*node)->next;
         node = &(*node)->next->next) {
        node_t *tmp = *node;
        *node = (*node)->next;
        tmp->next = (*node)->next;
        (*node)->next = tmp;
    }
    return head;
}

void swap_mod(node_t **head)
{
    for (; *head && (*head)->next; head = &(*head)->next->next) {
        node_t *indirect = *head;
        *head = (*head)->next;
        indirect->next = (*head)->next;
        (*head)->next = indirect;
    }
}

node_t *reverse(node_t *head)
{
    node_t *cursor = NULL;
    while (head) {
        node_t *next = head->next;
        head->next = cursor;
        cursor = head;
        head = next;
    }
    return cursor;
}

void reverse_mod(node_t **head)
{
    node_t *cursor = NULL;
    while (*head) {
        node_t *next = (*head)->next;
        (*head)->next = cursor;
        cursor = *head;
        *head = next;
    }
    *head = cursor;
}

node_t *rev_recursive(node_t *head, node_t *cursor)
{
    if (!head)
        return cursor;
    node_t *next = head->next;
    head->next = cursor;
    cursor = head;
    head = next;
    return rev_recursive(head, cursor);
}

void print_list(node_t *head)
{
    int i = 0;
    for (node_t *current = head; current; current = current->next) {
        printf("%d ", current->value);
        i++;
        if (i > 10)
            break;
    }
    printf("\n");
}

void shuffle(node_t **head)
{
    srand(time(NULL));
    int size = 0;
    node_t *count = *head;
    while (count) {
        size++;
        count = count->next;
    }
    while (size > 1) {
        node_t *swap, *swap_prev, *tail, *tail_prev;
        int ran = rand() % size + 1;
        printf("%d\n", ran);
        if (ran == size) {
            size--;
            continue;
        }
        swap = tail = *head;
        for (int i = 0; i < size - 1; i++) {
            tail_prev = tail;
            tail = tail->next;
        }
        for (int j = 0; j < ran - 1; j++) {
            swap_prev = swap;
            swap = swap->next;
        }
        if (ran == size - 1) {
            swap->next = tail->next;
            tail->next = swap;
        } else {
            node_t *tmp_next = swap->next;
            swap->next = tail->next;
            tail->next = tmp_next;
            tail_prev->next = swap;
        }
        if (ran > 1)
            swap_prev->next = tail;
        else
            *head = tail;
        size--;
        print_list(*head);
    }
}

int main(int argc, char const *argv[])
{
    node_t *head = NULL;

    print_list(head);

    add_entry(&head, 72);
    add_entry(&head, 101);
    add_entry(&head, 108);
    add_entry(&head, 109);
    add_entry(&head, 110);
    add_entry(&head, 111);

    print_list(head);

    node_t *entry = find_entry(head, 101);
    remove_entry(&head, entry);

    entry = find_entry(head, 111);
    remove_entry(&head, entry);

    print_list(head);

    /* swap pair.
     * See https://leetcode.com/problems/swap-nodes-in-pairs/
     */
    // head = swap_pair(head);
    swap_mod(&head);
    print_list(head);

    // head = reverse(head);
    // reverse_mod(&head);
    head = rev_recursive(head, NULL);
    print_list(head);
    add_entry(&head, 45);
    add_entry(&head, 874);
    add_entry(&head, 12);
    add_entry(&head, 144);
    print_list(head);
    shuffle(&head);

    return 0;
}
