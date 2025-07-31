#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_LEN 100

typedef struct Node
{
    char bookTitle[MAX_LEN];
    struct Node *next;
} Node;

typedef struct Stack
{
    Node *top;
} Stack;

typedef struct Queue
{
    Node *front;
    Node *rear;
} Queue;

Node *crNode()
{
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n)
    {
        printf("cap phat that bai.\n");
        return NULL;
    }
    strcpy(n->bookTitle, "");
    n->next = NULL;
    return n;
}

Stack *crStack()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if (!s)
    {
        printf("cap phat that bai.\n");
        return NULL;
    }
    s->top = NULL;
    return s;
}

Queue *crQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (!q)
    {
        printf("cap phat that bai.\n");
        return NULL;
    }
    q->front = q->rear = NULL;
    return q;
}

// kiem tra rỗng
bool emptyStack(Stack *s)
{
    return s == NULL || s->top == NULL;
}

bool emptyQueue(Queue *q)
{
    return q == NULL || q->front == NULL;
}

// trả về node cuối trong queue
Node *endQueue(Queue *q)
{
    Node *temp = q->front;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    return temp;
}

// the vao stack
void pushStack(Stack **s, Node *n)
{
    // nếu rỗng
    if (*s == NULL || (*s)->top == NULL)
    {
        (*s)->top = n;
        return;
    }
    n->next = (*s)->top;
    (*s)->top = n;
}

Node *popStack(Stack **s)
{
    if (*s == NULL || (*s)->top == NULL)
    {
        printf("ds rong.\n");
        return NULL;
    }
    Node *temp = (*s)->top;
    (*s)->top = (*s)->top->next;
    temp->next = NULL;
    return temp;
}

// int stack
void showStack(Stack *s)
{
    int i = 1;
    Node *temp = s->top;
    while (temp != NULL)
    {
        printf("%d: %s\n", i, temp->bookTitle);
        temp = temp->next;
        i++;
    }
    printf("\n");
}

// them vào queue
void pushQueue(Queue **q, Node *n)
{
    if (*q == NULL || (*q)->front == NULL)
    {
        (*q)->front = n;
        (*q)->rear = n;
        return;
    }
    (*q)->rear->next = n;
    (*q)->rear = n;
}

// lấy khỏi queue
Node *popQueue(Queue **q)
{
    if (*q == NULL || (*q)->front == NULL)
    {
        printf("ds rong.\n");
        return NULL;
    }
    Node *temp = (*q)->front;
    (*q)->front = (*q)->front->next;
    temp->next = NULL;
    return temp;
}

void showQueue(Queue *q)
{
    Node *temp = q->front;
    int i = 1;
    while (temp != NULL)
    {
        printf("%d: %s\n", i, temp->bookTitle);
        temp = temp->next;
        i++;
    }
    printf("\n");
}

void freeStack(Stack *s)
{
    Node *temp = s->top;
    while (temp != NULL)
    {
        Node *t = temp;
        temp = temp->next;
        free(t);
    }
    free(s);
}

void freeQueue(Queue *q)
{
    Node *temp = q->front;
    while (temp != NULL)
    {
        Node *t = temp;
        temp = temp->next;
        free(t);
    }
    free(q);
}

void menu()
{
    printf("1. Mo sach moi\n");
    printf("2. Dong sach hien tai\n");
    printf("3. Xem sach gan nhat\n");
    printf("4. Lich su dong sach\n");
    printf("5. Khoi phuc sach\n");
    printf("6. Hien thi sach dang mo\n");
    printf("7. Thoat\n");
    printf("<------------------->\n");
    printf("Lua chon cua ban-> ");
}
// show top stack
void thetop(Stack *s)
{
    if (s == NULL || s->top == NULL)
        printf("ds rong.\n");
    else
        printf("%s\n", s->top->bookTitle);
}

int main()
{
    Stack *bookStack = crStack();
    Queue *closeQueue = crQueue();
    int choice;
    char bookname[MAX_LEN];
    do
    {
        menu();
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1: // mo sach moi
            printf("nhap ten sach moi.\n");
            fgets(bookname, sizeof(bookname), stdin);
            bookname[strcspn(bookname, "\n")] = '\0';
            Node *n = crNode();
            strcpy(n->bookTitle, bookname);
            pushStack(&bookStack, n);
            showStack(bookStack);
            break;
        case 2: // dong sach hien tai
            pushQueue(&closeQueue, popStack(&bookStack));
            break;
        case 3:
            thetop(bookStack);
            break;
        case 4:
            showQueue(closeQueue);
            break;
        case 5:
            pushStack(&bookStack, popQueue(&closeQueue));
            break;
        case 6:
            showStack(bookStack);
            break;
        case 7:
            freeStack(bookStack);
            freeQueue(closeQueue);
            return;
        default:
            break;
        }
    } while (choice != 7);

    freeStack(bookStack);
    freeQueue(closeQueue);
    return 0;
}