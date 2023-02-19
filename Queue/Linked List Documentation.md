# Linked List Documentation
![image](https://user-images.githubusercontent.com/78487146/219937496-8d81238a-a3a9-4d75-b808-190720056f6d.png)

| Function                                                          | Description                                                      |
|-------------------------------------------------------------------|------------------------------------------------------------------|
|Node* list_create_node(const int value);                           | Returns a pointer to the Node, otherwise NULL | 
|Node* list_clone(Node** destination, Node* source);                | Clones the source List to destination. Returns a pointer to the cloned List, otherwise NULL. Destination can be NULL |
|int list_insert(Node** head, const int index, const int value);    | Inserts a Node in the specified position. Returns 1 on success, otherwise 0 |
|int list_delete(Node** head, const int index);                     | Deletes a Node in the specified position. Returns 1 on success, otherwise 0 |
|int list_append(Node** head, const int value);                     | Appens a Node to the List. Returns 1 on success, otherwise 0 |
|int list_find_index(Node* head, const int value);                  | Finds the index of a Node that holds the value. Returns index on success, otherwise -1 |
|int list_get_size(Node* head);                                     | Returns the size of the List |
|int list_set_value(Node* head, const int index, const int value);  | Sets the value of a Node in the specified position. Returns 1 on success, otherwise 0 |
|int list_set_first(Node* head, const int value);                   | Sets the value of the first Node. Returns 1 on success, otherwise 0 |
|int list_set_last(Node* head, const int value);                    | Sets the value of the last Node. Returns 1 on success, otherwise 0 |
|int list_get_value(Node* head, const int index);                   | Returns the value of a Node in the specified position. |
|int list_get_first(Node* head);                                    | Returns the value of the first Node. |
|int list_get_last(Node* head);                                     | Returns the value of the last Node. |
|int list_is_empty(Node* head);                                     | Returns 1 if the size of the list is 0, otherwise 0 |
|int list_is_full();                                                | Returns 1 if no memory can be allocated for a new Node, otherwise 0 |
|char* list_to_string(Node* head);                                  | Converts the values of a List to a string. Returns a pointer to the start of the string, otherwise NULL |
|void list_sort(Node** head);                                       | Sorts a List in ascending order |
|void list_destroy(Node** head);                                    | Frees all the Nodes of a List from memory |
