#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 200

typedef struct Node
{
    char content[MAX_LEN]; // Câu hỏi hoặc hành động
    int isAction;          // 1 nếu là hành động cuối (lá), 0 nếu là câu hỏi
    struct Node *yesChild; // Nếu người chơi chọn "Yes"
    struct Node *noChild;  // Nếu người chơi chọn "No"
} Node;

typedef struct Nqueue
{
    Node *data;
    struct Nqueue *next;
} Nqueue;

typedef struct queue
{
    Nqueue *front;
    Nqueue *rear;
} queue;

Node *crNode()
{
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n)
    {
        printf("cap phat that bai.\n");
        return NULL;
    }
    n->isAction = 1;
    strcpy(n->content, "");
    n->noChild = n->yesChild = NULL;
    return n;
}

Nqueue *crNqueue(Node *n)
{
    Nqueue *t = (Nqueue *)malloc(sizeof(Nqueue));
    if (!t)
    {
        printf("cap phat that bai.\n");
        return NULL;
    }
    t->data = n;
    t->next = NULL;
    return t;
}

queue *crQueue()
{
    queue *q = (queue *)malloc(sizeof(queue));
    if (!q)
    {
        printf("cap phat that bai.\n");
        return NULL;
    }
    q->front = q->rear = NULL;
    return q;
}

// thêm vào queue
void push(queue *q, Node *n)
{
    Nqueue *temp = crNqueue(n);
    if (q == NULL || q->front == NULL)
    {
        q->front = temp;
        q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

Node *pop(queue *q)
{
    if (q == NULL || q->front == NULL)
    {
        printf("ds rong.\n");
        return NULL;
    }
    Nqueue *temp = q->front;
    Node *t = temp->data;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return t;
}

bool empty(queue *q)
{
    return q == NULL || q->front == NULL;
}

// giải phóng queue
void freeQueue(queue *q)
{
    Nqueue *temp = q->front;
    while (temp != NULL)
    {
        Nqueue *t = temp;
        temp = temp->next;
        free(t->data);
        free(t);
    }
    free(q);
}

void levalPush(Node *root, Node *n)
{
    if (root == NULL || n == NULL)
    {
        root = n;
        return;
    }
    queue *q = crQueue();
    push(q, root);
    while (!empty(q))
    {
        Node *cur = pop(q);
        if (cur->yesChild == NULL)
        {
            cur->isAction = 0;
            cur->yesChild = n;
            freeQueue(q);
            return;
        }
        else
        {
            push(q, cur->yesChild);
        }
        if (cur->noChild == NULL)
        {
            cur->isAction = 0;
            cur->noChild = n;
            freeQueue(q);
            return;
        }
        else
        {
            push(q, cur->noChild);
        }
    }
    freeQueue(q);
}

void startgame(Node *root)
{
    if (root == NULL || root->content[0] == '\0')
    {
        printf("cay khong ton tai.\n");
        return;
    }
    queue *q = crQueue();
    push(q, root);
    char choice[10];
    while (!empty(q))
    {
        Node *temp = pop(q);
        if (temp->isAction = 0)
        {
            printf("%S.\n", temp->content);
            printf("Yes: trái.\nNo: phải\n!=: dừng\n");
            printf("lua chon cau ban: ");
            fgets(choice, sizeof(choice), stdin);
            choice[strcspn(choice, "\n")] = '\n';
            if (choice == "yes" || choice == "Yes" || choice == "YES")
            {
                push(q, temp->yesChild);
            }
            else if (choice == "NO" || choice == "No" || choice == "no")
            {
                push(q, temp->noChild);
            }
            else
            {
                printf("ket thuc tro choi.\n");
                return;
            }
        }
        else if (temp->isAction == 1)
        {
            printf("ban da di den cuoi.\n");
            return;
        }
    }
}

void out(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    queue *q = crQueue();
    push(q, root);
    while (!empty(q))
    {
        Node *cur = pop(q);
        printf("%s.\n", cur->content);
        if (cur->yesChild != NULL)
        {
            push(q, cur->yesChild);
        }
        if (cur->noChild != NULL)
        {
            push(q, cur->noChild);
        }
    }
}

void menu()
{
    printf("1: Bat dau tro choi\n");
    printf("2: hien thi cay quyet dinh\n");
    printf("3: TThem cau hoi hanh dong\n");
    printf("4: Xoa 1 nut trong cay\n");
    printf("5: thoat\n");
    printf("<------------>\n");
    printf("lua chon cua ban: ");
}

int main()
{
    Node *root = crNode();
    int choice;
    char whattt[50];
    {
        menu();
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            startgame(root);
            break;
        case 2:
            out(root);
            break;
        case 3:
            printf("nhap cau hỏi.\n");
            fgets(whattt, sizeof(whattt), stdin);
            whattt[strcspn(whattt, "\n")] = '\0';
            Node *newnode = crNode();
            strcpy(newnode->content, whattt);
            levalPush(root, newnode);
            break;
        case 4:
            break;
        case 5:
            return 0;
        default:
            break;
        }
    }
    while (choice != 5)
        ;

    return 0;
}