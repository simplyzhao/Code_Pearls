/* transform a binary search tree into a sorted doubly linked list in place.
 * Example:
 * Given:
 *                  9
 *                 / \
 *                6   12
 *               /   /  \
 *              2   10  37
 *                   \
 *                    11
 * Expected Output:
 * 2 - 6 - 9 - 10 - 11 - 12 - 37
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
    struct _Node *left;     /* prev */
    struct _Node *right;    /* next */
    int value;
} Node;

void
insert_bst(Node **ppNode, int value)
{
    if (*ppNode == NULL) /* target Node found */
    {
        *ppNode = (Node *)malloc(sizeof(Node));
        (*ppNode)->left = NULL;
        (*ppNode)->right = NULL;
        (*ppNode)->value = value;
        return;
    }

    insert_bst((*ppNode)->value >= value ? &((*ppNode)->left) : &((*ppNode)->right), value);
}

void
bst2list(Node *root, Node **head, Node **tail)
{
    Node *l_head, *l_tail, *r_head, *r_tail;
    l_head = l_tail = r_head = r_tail = NULL;

    if (root == NULL)
    {
        *head = *tail = NULL;
        return;
    }

    bst2list(root->left, &l_head, &l_tail);
    if (l_head)
    {
        l_tail->right = root;
        root->left = l_tail;
    }
    bst2list(root->right, &r_head, &r_tail);
    if (r_head)
    {
        root->right = r_head;
        r_head->left = root;
    }
    
    *head = l_head ? l_head : root;
    *tail = r_head ? r_tail : root;
    return;
}

void
list_display(Node *head, Node *tail)
{
    printf("From Left to Right:\n");
    while (head != NULL)
    {
        printf("%p\t%p\t%p\t%d\n", head->left, head, head->right, head->value);
        head = head->right;
    }
    printf("From Right to Left:\n");
    while (tail != NULL)
    {
        printf("%p\t%p\t%p\t%d\n", tail->left, tail, tail->right, tail->value);
        tail = tail->left;
    }
    return;
}

int
main(int argc, char **argv)
{
    Node *root, *head, *tail;
    root = head = tail = NULL;
    /* create the binary search tree */
    insert_bst(&root, 9);
    insert_bst(&root, 6);
    insert_bst(&root, 12);
    insert_bst(&root, 2);
    insert_bst(&root, 10);
    insert_bst(&root, 37);
    insert_bst(&root, 11);
    /* do the transformation */
    bst2list(root, &head, &tail);
    list_display(head, tail);
    /* release the bst/list memory */
}
