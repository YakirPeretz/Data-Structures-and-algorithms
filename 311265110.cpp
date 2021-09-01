// Task 3 - Data Structures and Algorithms -2021
// Yakir Peretz- 311265110
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "math.h"
#include <iostream> //for c++

using namespace std;

class GasStation {
public:
	int dist, cost;
	bool operator<(GasStation const &other) const {
		return dist < other.dist;
	}
	bool operator<=(GasStation const &other) const {
		return dist < other.dist;
	}
};


typedef struct point {
	int x;
	int y;
}point;

typedef struct circle {
	int x, y;
	int radius;
}circle;

typedef struct pointDist {
	int x, y;
	int dist;
}pointDist;

class Stack {
public:
	int top;
	int stack[50001]{};
	Stack() { top = -1; }
	void push(int key) {
		top++;
		stack[top] = key;
	};
	int pop() {
		top--;
		return stack[top + 1];
	}
	int peek() { return stack[top]; }
	bool empty() const { return top == -1; }
};

class Queue {
public:
	int front, rear, size;
	unsigned capacity;
	point* arr;
};

class QueueDist {
public:
	int front, rear, size;
	unsigned capacity;
	pointDist* arr;
};
template<typename T>
void swap(T *a, T *b);
template<typename T>
void QuickSort(T arr[], int low, int high);
template<typename T>
int partition(T arr[], int low, int high);

long long int iceland_trip();
int farthest_enemy();
int maze_runner();

Queue* createQueue(unsigned capacity);
void deleteQeque(Queue *Q);
//point rear(Queue* queue); // not in use in this program
point peek(Queue* queue);
void dequeue(Queue* queue);
void enqueue(Queue* queue, int x, int y);
bool isEmpty(Queue* queue);
bool isFull(Queue* queue);
QueueDist* createQueueD(unsigned capacity);
void deleteQequeD(QueueDist *Q);
pointDist peekD(QueueDist* queue);
void dequeueD(QueueDist* queue);
void enqueueD(QueueDist* queue, int x, int y, int dist);
bool isEmptyD(QueueDist* queue);
bool isFullD(QueueDist* queue);
int maxDist(int **arr, int N, int M);
bool isInside(circle circ, int x, int y);
int ShortestPath(int **grid, int n, int m);


int main(int argc, char** argv) {
	int choice;
	scanf("%d", &choice);
	if (choice == 1) printf("%lld\n", iceland_trip());
	if (choice == 2) printf("%d\n", farthest_enemy());
	if (choice == 3) printf("%d\n", maze_runner());
	return 0;
}


/*
 * Iceland trip- O(NlogN):
 * QuickSort: NlogN. running time for next_smaller(stack) O(N).
 */

long long int iceland_trip()
{
	int N, maxGas, curGas;
	int dist, *smaller;
	Stack s;
	GasStation *stations;
	scanf("%d %d %d %d", &N, &maxGas, &curGas, &dist);
	stations = (GasStation*)malloc(sizeof(GasStation)*N);
	smaller = (int*)malloc(sizeof(int)*N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &stations[i].dist);
		scanf("%d", &stations[i].cost);
	}
	QuickSort<GasStation>(stations, 0, N - 1); // O(NlogN)

	for (int i = N - 1; i >= 0; i--)
	{
		while (!s.empty() && stations[s.peek()].cost >= stations[i].cost)
		{
			s.pop();
		}
		smaller[i] = s.empty() ? -1 : s.peek();
		s.push(i);
	}

	curGas -= stations[0].dist;
	long long cost = 0;
	for (int i = 0; i < N; i++)
	{
		if (curGas < 0) // case we can't reach the first Gas station
		{
			free(stations);
			free(smaller);
			return -1;
		}
		int GasNeeded = fmin(maxGas, (smaller[i] == -1 ? dist :
			stations[smaller[i]].dist) - stations[i].dist);
		if (GasNeeded > curGas) // case we can't reach the next cheaper Gas Station
		{
			cost += (long long)(GasNeeded - curGas)* (long long)stations[i].cost;
			curGas = GasNeeded;
		}
		curGas -= (i == N - 1 ? dist : stations[i + 1].dist) - stations[i].dist; // moving to the next station
	}
	free(stations);
	free(smaller);
	if (curGas < 0)
		return -1;
	else
		return cost;
}


/*
 * Farthest enemy- O(N*M): fill the Matrix- O(M*N). MaxDist- O(M*N)
*/
int farthest_enemy()
{
	int N, M, solution = 0;
	int i, j, **mat;
	scanf("%d", &N);
	scanf("%d", &M);
	mat = (int**)malloc(sizeof(int*) * N);
	for (i = 0; i < N; i++)
		mat[i] = (int*)malloc(sizeof(int) * M);
	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++)
			scanf("%d", &mat[i][j]);

	solution = maxDist(mat, N, M);

	for (i = 0; i < N; i++)
		free(mat[i]);
	free(mat);

	return solution;
}



/*
 * Maze Runner problem- O(N*M*K)
 * BFS- O(M*N), Fill the matrix with the circles- O(K*M*N)
 */

int maze_runner()
{
	int n, m, k, i, j, l;
	int **grid;
	int solution;
	circle *arr_cir;
	scanf("%d", &n);
	scanf("%d", &m);
	scanf("%d", &k);
	grid = (int**)malloc(sizeof(int*) * n);
	for (i = 0; i < n; i++)
		grid[i] = (int*)malloc(sizeof(int) * m);
	arr_cir = (circle*)malloc(sizeof(circle)*k);
	for (i = 0; i < k; i++)
	{
		scanf("%d", &arr_cir[i].radius);
		scanf("%d", &arr_cir[i].x);
		scanf("%d", &arr_cir[i].y);
	}
	//initialize the grid
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			grid[i][j] = 1;

	for (l = 0; l < k; l++)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < m; j++)
			{
				if (isInside(arr_cir[l], i, j))
					grid[i][j] = 0;
			}
		}
	}

	solution = ShortestPath(grid, n, m);
	for (i = 0; i < n; i++)
		free(grid[i]);
	free(grid);
	return solution;
}




// find the Maximum of all distances to the nearest 1 cell from any 0 cell in a Binary matrix
// O(M*N)- scanning all the Matrix and insert to the Queue.
// O(M*N)- BFS traversal layer by layer.
int maxDist(int **arr, int N, int M)
{
	int ans = -1;
	point p;
	Queue *q = createQueue(N*M);
	int directions[4][2] = { {0,1},{1,0},{0,-1},{-1,0} }; // Directions traversable from a given a particular cell
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (arr[i][j] == 1)
				enqueue(q, i, j);
		}
	}
	// if the matrix contains only 0s or 1s
	if (isEmpty(q) || q->size == M * N)
		return -1;

	while (q->size)
	{
		int count = q->size;

		while (count--)
		{
			// access every 1-cell
			p = peek(q);
			dequeue(q);
			// Traverse all possible directions from the cells
			for (int i = 0; i < 4; i++)
			{
				int x = p.x + directions[i][0];
				int y = p.y + directions[i][1];
				//check if the cell is inside the matrix or contains a 1
				if (x < 0 || x >= N || y < 0 || y >= M || arr[x][y])
					continue;
				enqueue(q, x, y);
				arr[x][y] = 1;

			}
		}
		++ans;
	}
	deleteQeque(q);
	return ans;
}

// // O(M*N)- BFS traversal
int ShortestPath(int **grid, int n, int m)
{
	int ans = -1;
	point p;
	pointDist curr;
	QueueDist *q = createQueueD(n*m);
	// Directions traversable from a given a particular cell
	int directions[8][2] = { {-1,-1},{-1,0},{-1,1},{0,-1} ,{0,1}, {1,-1}, {1,0}, {1,1} };
	// check if the starting point or the end point are can't be reach
	if (!grid[0][0] || !grid[n - 1][m - 1])
		return ans;

	bool **visited;
	visited = (bool**)malloc(sizeof(bool*) * n);
	for (int i = 0; i < n; i++)
		visited[i] = (bool*)malloc(sizeof(bool) * m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			visited[i][j] = false;
		}
	}
	visited[0][0] = true;
	enqueueD(q, 0, 0, 0);
	while (q->size)
	{
		curr = peekD(q);
		p.x = curr.x;
		p.y = curr.y;
		if (p.x == n - 1 && p.y == m - 1)
		{
			for (int i = 0; i < n; i++)
				free(visited[i]);
			free(visited);
			deleteQequeD(q);
			return curr.dist;
		}
		dequeueD(q);
		for (int i = 0; i < 8; i++)
		{
			int x = p.x + directions[i][0];
			int y = p.y + directions[i][1];
			if (x >= 0 && x < n && y >= 0 && y < m &&grid[x][y] && !visited[x][y])
			{
				visited[x][y] = true;
				enqueueD(q, x, y, curr.dist + 1);
			}
		}
	}
	for (int i = 0; i < n; i++)
		free(visited[i]);
	free(visited);
	deleteQequeD(q);
	return -1; // in case the last cell can't be reached;
}


// Constructor to initialize a queue
Queue* createQueue(unsigned capacity)
{
	Queue* queue = new Queue();
	queue->capacity = capacity;
	queue->front = queue->size = 0;

	// This is important, see the enqueue
	queue->rear = capacity - 1;
	queue->arr = new point[queue->capacity];
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
void enqueue(Queue* queue, int x, int y)
{
	if (isFull(queue))
		return;
	queue->rear = (queue->rear + 1)
		% queue->capacity;
	queue->arr[queue->rear].x = x;
	queue->arr[queue->rear].y = y;
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
point peek(Queue* queue)
{
	point p;
	p.x = -1;
	p.y = -1;
	if (isEmpty(queue))
		return p;
	return queue->arr[queue->front];
}

// Function to get rear of queue
/*
point rear(Queue* queue)
{
	point p;
	p.x=-1;
	p.y=-1;
	if (isEmpty(queue))
		return p;
	return queue->arr[queue->rear];
}

*/
bool isInside(circle circ, int x, int y)
{
	// Compare radius of circle with distance
	// of its center from given point
	double temp1, temp2;
	temp1 = fmin(fabs(circ.x - 0.5 - x), fabs(circ.x - x));
	temp1 = fmin(temp1, fabs(circ.x + 0.5 - x));
	temp2 = fmin(fabs(circ.y - 0.5 - y), fabs(circ.y - y));
	temp2 = fmin(temp2, fabs(circ.y + 0.5 - y));
	if (temp1*temp1 + temp2 * temp2 <= circ.radius*circ.radius)
		return true;
	else
		return false;
}


// Constructor to initialize a queue
QueueDist* createQueueD(unsigned capacity)
{
	QueueDist* queue = new QueueDist();
	queue->capacity = capacity;
	queue->front = queue->size = 0;

	// This is important, see the enqueue
	queue->rear = capacity - 1;
	queue->arr = new pointDist[queue->capacity];
	return queue;
}
//delete Queue
void deleteQequeD(QueueDist *Q)
{
	free(Q->arr);
}

// Queue is full when size
// becomes equal to the capacity
bool isFullD(QueueDist* queue)
{
	return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
bool isEmptyD(QueueDist* queue)
{
	return (queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
void enqueueD(QueueDist* queue, int x, int y, int dist)
{
	if (isFullD(queue))
		return;
	queue->rear = (queue->rear + 1)
		% queue->capacity;
	queue->arr[queue->rear].x = x;
	queue->arr[queue->rear].y = y;
	queue->arr[queue->rear].dist = dist;
	queue->size = queue->size + 1;
}

// Function to remove an item from queue.
// It changes front and size
void dequeueD(QueueDist* queue)
{
	if (isEmptyD(queue))
		return;
	queue->front = (queue->front + 1)
		% queue->capacity;
	queue->size = queue->size - 1;
}

// Function to get front of queue
pointDist peekD(QueueDist* queue)
{
	pointDist p;
	p.x = -1;
	p.y = -1;
	p.dist = -1;
	if (isEmptyD(queue))
		return p;
	return queue->arr[queue->front];
}

template<typename T>
void swap(T *a, T *b) {
	T temp;
	temp.cost = a->cost;
	temp.dist = a->dist;
	a->cost = b->cost;
	a->dist = b->dist;
	b->cost = temp.cost;
	b->dist = temp.dist;
}
template<typename T>
int partition(T arr[], int low, int high) {
	T pivot = arr[high];    // pivot
	int i = (low - 1);  // Index of smaller element

	for (int j = low; j <= high - 1; j++) {
		// If current element is smaller than or
		// equal to pivot
		if (arr[j] <= pivot) {
			i++;    // increment index of smaller element
			swap<T>(&arr[i], &arr[j]);
		}
	}
	swap<T>(&arr[i + 1], &arr[high]);
	return (i + 1);
}

template<typename T>
void QuickSort(T arr[], int low, int high) {
	if (low < high) {
		/* pi is partitioning index, arr[p] is now
		   at right place */
		int pi = partition<T>(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		QuickSort<T>(arr, low, pi - 1);
		QuickSort<T>(arr, pi + 1, high);
	}
}