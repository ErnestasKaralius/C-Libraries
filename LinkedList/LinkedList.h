#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

typedef struct LinkedList {
    int value;
    struct LinkedList* next;
} Node;

Node* list_create_node(const int value);
Node* list_clone(Node** destination, Node* source);

int list_insert(Node** head, const int index, const int value);
int list_delete(Node** head, const int index);
int list_append(Node** head, const int value);

int list_find_index(Node* head, const int value);
int list_get_size(Node* head);

int list_set_value(Node* head, const int index, const int value);
int list_set_first(Node* head, const int value);
int list_set_last(Node* head, const int value);

int list_get_value(Node* head, const int index);
int list_get_first(Node* head);
int list_get_last(Node* head);

int list_is_empty(Node* head);
int list_is_full();

char* list_to_string(Node* head);
void list_sort(Node** head);
void list_destroy(Node** head);

#endif // LINKEDLIST_H_INCLUDED
