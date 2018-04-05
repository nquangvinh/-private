
#include <stdio.h>
#include <stdlib.h>
 
struct Node 
{
    int data;
    struct Node *next;
};

struct Node* head = NULL;
struct Node* tail = NULL;

unsigned long sumTotal = 0;

void display(int displayData)
{
    printf("Node value :%d\n", displayData);
    return;
}

void sum(int sumData)
{
    sumTotal += sumData;
    return;
}


void func_todo_LinkedList(struct Node *head, void (*func_ptr)(int))
{
    sumTotal = 0;
    while (head != NULL)
    {
        (*func_ptr)(head->data);
        head = head->next;
    }

    if (*func_ptr == sum)
    {
        printf("sumTotal = %lu \n", sumTotal);
    }
    return;
}

void addTail(int newdataTail)
{
    struct Node *newNode_Tail = NULL;
    newNode_Tail = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode_Tail)
    {
        printf("Malloc failed\n");
        return;
    }
    else
    {
        if ((tail == NULL) && (head == NULL))
        {
            printf("Linked list is empty. Cannot add node to the tail!\n");
            return;
        }

        newNode_Tail->data = newdataTail;
        newNode_Tail->next = NULL;
        tail->next = newNode_Tail;
        tail = newNode_Tail;
    }
}

void addHead(int newdataHead)
{
    struct Node *newNode_Head = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode_Head)
    {
        printf("Malloc failed\n");
        return;
    }
    else
    {
        newNode_Head->data = newdataHead;
        if ((head == NULL) && (tail == NULL))
        {
            newNode_Head->next = NULL;
            head = newNode_Head;
            tail = newNode_Head;
            return;
        }

        newNode_Head->next = head;
        head = newNode_Head;
    }
}

void func_Free_LinkedList(struct Node **head)
{
    struct Node * nodeToFree = *head;
    struct Node * tmpNodeNext;
    while (nodeToFree != NULL)
    {
        tmpNodeNext = nodeToFree->next;
        free(nodeToFree);
        nodeToFree = tmpNodeNext;
    }
    *head = NULL;
}

void delete(struct Node **headNode, struct Node **deleteNode)
{
    struct Node *previousNode = *headNode, *tmp;

    // if the Head is a deleteNode
    if (previousNode != NULL && previousNode == *(deleteNode))
    {
        head = previousNode->next;        // Changed global head
        free(previousNode);               // free old head
        return;
    }
    else
    {
        while (previousNode != NULL)
        {
            if (previousNode->next == *(deleteNode))
            {
                tmp = previousNode->next;

                // if the Tail is deleted Node
                if (tmp->next == NULL)
                {
                    tail = previousNode;
                    tail->next = NULL;
                }

                free(previousNode->next);
                previousNode->next = tmp->next;
                return;
            }
            previousNode = previousNode->next;
        }
        return;
    }
}


void delete_OneEntity_value(struct Node **head, int value)
{
    struct Node * currentNode = *head;
    while (currentNode != NULL)
    {
        if (currentNode->data == value)
        {
            delete(head, &currentNode);
        }
        currentNode = currentNode->next;
    }
}

void delete_OneEntity_position(struct Node **head, int position)
{
    struct Node * currentNode = *head;
    int count = 0;
    while (currentNode != NULL )
    {
        if(count == position)
        {
            delete(head, &currentNode);
            return;
        }
        count++;
        currentNode = currentNode->next;
    }
}

int main()
{

    int i;
    for (i=5; i < 10; i++)
    {
        addHead(i);
    }
    for (i=5; i < 10; i++)
    {
        addTail(i);
    }

    addHead(1000);
    addTail(123);

    func_todo_LinkedList(head, display);
    func_todo_LinkedList(head, sum);

    printf("\n");
    delete_OneEntity_value(&head, 123);
    delete_OneEntity_value(&head, 7);
    delete_OneEntity_position(&head, 1);
    delete_OneEntity_position(&head, 56);
    func_todo_LinkedList(head, display);
    func_todo_LinkedList(head, sum);

    printf("\n");
    addHead(999999);
    addTail(12673512);
    addTail(77777777);
    func_todo_LinkedList(head, display);
    func_todo_LinkedList(head, sum);

    func_Free_LinkedList(&head);

    return 0;
}