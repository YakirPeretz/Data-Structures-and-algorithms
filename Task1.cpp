//// Yakir Peretz - 311265110
//// Task 1- Algorithms and Data Structures
#define _CRT_SECURE_NO_WARNINGS
#include <iostream> //for c++
using namespace std;

typedef struct list {
    int value;
    list* prev;
}list;
// class to create a Stack
class Stack {
    list* tos;
public:
    Stack() { tos = NULL; };
    ~Stack();
    void push(int num);
    int pop();
    bool empty() const;
    int peek() const;
};//stack class implementation

// A class of Deque
class Deque
{
public:
    int front, rear , size;
    unsigned int capacity;
    int *arr;
};
Deque * createdeQue(unsigned int cap)
{
    Deque *Q = new Deque();
    Q->capacity = cap;
    Q->size = 0;
    Q->front = 0;
    Q->rear = cap -1;
    Q->arr = (int*) malloc(sizeof(int)*cap);
    return Q;
}
class Queue {
public:
    int front, rear, size;
    unsigned capacity;
    int* arr;
};

bool isEmpty(Deque * Q);
bool isFull(Deque * Q);
void insertRear(Deque * Q, int data);
void insertFront(Deque *Q, int data); // not in use in this program
void deleteFront(Deque *Q);
void deleteRear(Deque *Q);
void deleteDeque(Deque *Q);
int getFront (Deque *Q);
int getRear (Deque *Q);
Queue* createQueue(unsigned capacity);
void deleteQeque(Queue *Q);
int rear(Queue* queue); // not in use in this program
int peek(Queue* queue);
void dequeue(Queue* queue);
void enqueue(Queue* queue, int item);
bool isEmpty(Queue* queue);
bool isFull(Queue* queue);
int getMin(Deque *D);
void deque_element(Queue *Q, Deque *D);
void enque_element(Queue *Q, Deque *D,int element);

///// Solution for question 1- CNN max-pooling /////
// complexity: O(n)- n is the number of element in arr. every task take a linear time:
// Initialize left[] and right[]=linear with n; fill left[] and right[]= linear with n;
// initialize filter[]: linear with n; fill filter[]- linear with n.
// sum calculation- linear with n;
void question_1()
{
    int ans , n;
    int *arr;
    scanf("%d", &n);
    arr = (int*) malloc(sizeof(int) * n);
    for (int i=0; i < n; i++)
        scanf("%d", &arr[i]);
    Stack s_left,s_right;
    int *left, *right,*filter;
    left=(int*) malloc(sizeof(int)*(n+1));
    right=(int*) malloc(sizeof(int)*(n+1));
    filter=(int*) malloc(sizeof(int)*(n+1));
    // Initialize elements of left[] and right[] - O(n)
    for (int i=0; i<n; i++)
    {
        left[i] = -1;
        right[i] = n;
    }
    // Fill elements of left[]- Previous greater element on the left side of arr[i] - O(n)
    for (int i=0; i<n; i++)
    {
        while (!s_left.empty() && arr[s_left.peek()] <= arr[i])
            s_left.pop();

        if (!s_left.empty())
            left[i] = s_left.peek();

        s_left.push(i);
    }
    // Fill elements of right[]- next greater element on the right side of arr[i] - O(n)
    for (int i=n-1; i>=0; i--)
    {
        while (!s_right.empty() && arr[s_right.peek()] <= arr[i])
            s_right.pop();

        if (!s_right.empty())
            right[i] = s_right.peek();

        s_right.push(i);
    }
    // filter initialize to max value- O(n)
    for (int i=0; i<=n; i++)
        filter[i] = 1001;

    // filter width - O(n)
    for (int i = 0; i < n; i++) {
        int width = right[i] - left[i] - 1;
        filter[width] = min(filter[width], arr[i]);
    }
    //  ans=filter[n];
    // fill entries in filter that didn't fill yet and calculate the min sum - O(n)
    for (int i=n-1; i>=1; i--)
    {
        filter[i] = min(filter[i], filter[i + 1]);
    }
    ans=0;
    // calc the sum of all minimum values - O(n)
    for (int i=1; i<=n;i++)
        ans+=filter[i];

    free(left);
    free(right);
    free(filter);
    printf("%d\n", ans);
    free(arr);
}

///// Solution for Question 2- Job Performance analysis
// complexity: O(n)- n is the number of integers
// one loop that push or pop elements from the Queue, and calculate the ans.
// using an additional Deque(more space using) allow us to get the minimum of the Queue in O(1)
// the functions of the Queue and Deque are in O(1) complexity
void question_2()
{
    unsigned long long ans = 0;
    int n,num,i;
    scanf("%d", &n);
    Queue *Q=createQueue(n);
    Deque *D=createdeQue(n);
    int *arr;
    arr=(int*) malloc(sizeof(int)*n); // scan all the input to an array
    for (i=0;i<n;i++)
        scanf("%d", &arr[i]);
    // O(n)
    for (i=0;i<n;i++)
    {
        num=arr[i];
        if (isEmpty(Q)) // if the queue is empty
        {
            if(num==0) // there is no change in ans
                continue;
            else
            {
                enque_element(Q,D,num); //insert num to the queue - O(1)
                continue;
            }
        }
        else
        {
            if(num==0)
            {
                ans+=peek(Q)-getMin(D);// calculate the cost of the job and add to ans - O(1)
                deque_element(Q,D);// remove from Queue - O(1)
            }
            else
            {
                enque_element(Q,D,num); // insert num to the Queue - O(1)
            }
        }
    }
    deleteDeque(D);
    deleteQeque(Q);
    printf("%llu\n", ans);
}


///// Solution for Question 3- finding Max Palindrome substring /////
// Complexity: O(n^2)-n is the string length.
// We need n*n calculations to fill(or initialize) the Dynamic Matrix
// in the worst case we will need n*n calculation for ans
// after we fill the matrix we have the solution.

void question_3()
{
    int ans = 1;
    int i,j;
    int str_len; // length of the string
    char string[30] = {0};
    scanf("%d", &str_len);
    scanf("%s", string);
    ////////////////// create 2D array of booleans
    bool **Dynamic=  (bool**)malloc(str_len*sizeof(bool*)); //allocate memory of array of pointers of size str_len
    if(!Dynamic)
    {
        printf("Memory allocation failed\n");
        return;
    }

    for(i=0;i<str_len;i++)
    {
        if(!( Dynamic[i]= (bool*)malloc(str_len*sizeof(bool)))) // allocate memory if size str_len for each row
        {
            for(j=0;j<i;j++)
                free( Dynamic[j]);
            free (Dynamic);
            printf("Memory allocation failed\n");
            return;
        }
    }
    //the 2D array set to false - O(n^2)
    for (i=0;i<str_len;i++)
    {
        for(j=0;j<str_len;j++)
        {
            Dynamic[i][j]=false;
        }
    }

    // the Dynamic array of booleans indicate if the substring in the i,j coordinates of the string is a palindrome - O(n^2)
    for (i=str_len-1; i>=0;i--)
    {
        for(j=i;j<=str_len-1;j++)
        {
            if(i==j)
            {
                Dynamic[i][j]=true; // every single char is a palindrome
            }
            else if (string[i]==string[j]) // if two char in the string are equal
            {
                if (j-i==1) // check for substring in the length of 2
                {
                    Dynamic[i][j]=true;
                }
                else // check of substring in length greater than 2
                {
                    Dynamic[i][j]=Dynamic[i+1][j-1]; // check if the substring from the ith index to the jth index is a palindrome
                }
            }
            if (Dynamic[i][j] && (j-i>=ans)) // in case the substring is a palindrome- calculate the length (j-i)
            {
                ans=j-i+1;
            }
        }
    }
    for (i=0; i<str_len;i++)
        free (Dynamic[i]);
    free (Dynamic);
    printf("%d\n", ans);
}


int main(int argc, char** argv)
{
    int question;
    scanf("%d", &question);
    if (question == 1)
        question_1();
    else if (question == 2)
        question_2();
    else
        question_3();
    return 0;
}



//////////////////////////////////////////////////////////////////////////
Stack::~Stack() {
    list* kill = tos, * prev;
    while (kill) {
        prev = kill->prev;
        delete kill;
        kill = prev;
    }
}//stack Dtor

void Stack::push(int num) {
    //push number to stack top

    list* temp = new list;
    temp->prev = tos;
    temp->value = num;
    tos = temp;
}//stack::push

int Stack::pop() {
    //pop the top number on stack
    if (tos == 0)
        return -2;
    int temp_int = tos->value;
    list* temp_list = tos;
    tos = tos->prev;
    delete temp_list;
    return temp_int;
}//stack::pop

bool Stack::empty()const {
    //check if stack is empty
    if (tos == NULL)
        return true;
    return false;
}//stack::is_empty

int Stack::peek()const {
    //get the tos value
    if (tos == NULL)
        return -2;
    return tos->value;
}//stack::top_value}


// Destructor to free memory allocated to the queue
bool isEmpty(Deque * Q)
{
    return (Q->size == 0);
}
bool isFull(Deque * Q)
{
    return (Q->size == Q->capacity);
}

void insertRear(Deque * Q, int data)
{
    if(isFull(Q))
    {
        cout<<"deQue is full "<<endl;
        return;
    }
    Q->rear = (Q->rear + 1)%(Q->capacity);
    Q->arr[Q->rear] = data;
    Q->size++;
}
void insertFront(Deque *Q, int data)
{
    if(isFull(Q))
    {
        cout<<"dedeQue is full "<<endl;
        return;
    }
    if(Q->front == 0 && Q->rear == Q->capacity -1)
    {
        Q->rear = 0;
    }
    else if(Q->front == 0)
    {
        Q->front = Q->capacity -1;
    }
    else
    {
        Q->front--;
    }
    Q->arr[Q->front] = data;
    Q->size++;
}
void deleteFront(Deque *Q)
{
    if(isEmpty(Q))
    {
        cout<<"deQue is empty "<<endl;
        return;
    }
    Q->front = (Q->front +1)%(Q->capacity);
    Q->size--;
}
void deleteRear(Deque *Q)
{
    if(isEmpty(Q))
    {
        cout<<"deQue is empty "<<endl;
        return;
    }
    if(Q->rear == 0)
    {
        Q->rear = Q->capacity-1;
    }
    else
    {
        Q->rear--;
    }
    Q->size--;
}
int getFront (Deque *Q)
{
    if(isEmpty(Q))
    {
        cout<<"deQue is empty "<<endl;
        return -1;
    }
    return ( Q->arr[Q->front]);
}

int getRear (Deque *Q)
{
    if(isEmpty(Q) || Q->rear==(Q->capacity-1))
    {
        cout<<"deQue is empty "<<endl;
        return -1;
    }
    return ( Q->arr[Q->rear]);
}
void deleteDeque(Deque *Q)
{
    free(Q->arr);
}


// Constructor to initialize a queue
Queue* createQueue(unsigned capacity)
{
    Queue* queue = new Queue();
    queue->capacity = capacity;
    queue->front = queue->size = 0;

    // This is important, see the enqueue
    queue->rear = capacity - 1;
    queue->arr = new int[queue->capacity];
    return queue;
}
//delete Queue
void deleteQeque(Queue *Q)
{
    free(Q->arr);
}

// Queue is full when size
// becomes equal to the capacity
bool isFull(Queue* queue)
{
    return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
bool isEmpty(Queue* queue)
{
    return (queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
void enqueue(Queue* queue, int item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->arr[queue->rear] = item;
    queue->size = queue->size + 1;
}

// Function to remove an item from queue.
// It changes front and size
void dequeue(Queue* queue)
{
    if (isEmpty(queue))
        return;
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
}

// Function to get front of queue
int peek(Queue* queue)
{
    if (isEmpty(queue))
        return 0;
    return queue->arr[queue->front];
}

// Function to get rear of queue
int rear(Queue* queue)
{
    if (isEmpty(queue))
        return 0;
    return queue->arr[queue->rear];
}

//// the next 3 function are Special function to help get the minimum element of a Deque in O(1) time
//function that insert element to the front of deque
void enque_element(Queue *Q, Deque *D,int element)
{
    // If there is no element
    // in the queue
    if (Q->size==0)
    {
        enqueue(Q,element);
        insertRear(D,element);
    }
    else
    {
        enqueue(Q,element);

        // Pop the elements out
        // until the element at
        // back is greater than
        // current element
        while (!isEmpty(D) && getRear(D) > element)
        {
            deleteRear(D);
        }
        insertRear(D,element);
    }
}

void deque_element(Queue *Q, Deque *D)
{
    // Condition when the Minimum
    // element is the element at
    // the front of the Deque
    if (peek(Q) == getFront(D)) {
        dequeue(Q);
        deleteFront(D);
    }
    else {
        dequeue(Q);
    }
}

int getMin(Deque *D)
{
    return getFront(D);
}