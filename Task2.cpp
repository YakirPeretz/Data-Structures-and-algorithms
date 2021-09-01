//// Yakir Peretz - 311265110
//// Task 1- Algorithms and Data Structures
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>
#include <iostream> //for c++


using namespace std;


typedef struct Patient{
    long int id;
    double priority_val;
}Patient;

// A class for Max Heap
class MaxHeap
{
    int capacity; // maximum possible size of min heap

public:
    // Constructor
    MaxHeap(int capacity);

    // to heapify a subtree with the root at given index
    void MaxHeapify(int );
    // function to build max heap
    void  build_max_heap();

    int heap_size; // Current number of elements in max heap
    Patient *harr; // pointer to array of elements in heap
    // get parent
    int parent(int i) { return (i-1)/2; }

    // to get index of left child of node at index i
    int left(int i) { return (2*i + 1); }

    // to get index of right child of node at index i
    int right(int i) { return (2*i + 2); }

    // to extract the root which is the Maximum element
    void extractMax();


    // Returns the Max key (key at root) from Max heap
    int getMax() { return harr[0].id; }

};

int find_k_value();
long int transplant_list();
int sort_ip();
void swap ( int &a, int &b);
int partition(int arr[], int low,int high);
void QuickSort(int arr[], int low, int high);
void InsertIP(unsigned int arr[],int j);
void Reverse(unsigned int arr[],int size);
unsigned int getMax(unsigned int arr[], int n);
void countSort(unsigned int arr[], int n, unsigned long long exp);
void radixsort(unsigned int arr[], int n);
void insertionSort(int arr[], int n);
void swapPatient ( Patient &a, Patient &b);

int main()
{
    int choice = 0;
    scanf("%d", &choice);
    if (choice == 1)
        printf("%d\n", find_k_value());
    if (choice == 2)
        printf("%ld\n", transplant_list());
    if (choice == 3)
        printf("%d\n", sort_ip());
    return 0;
}

//Task 1- find the smallest value of the k'th value of consecuitive subsequences of length m
// loop- o(n).
// 1 time Quick sort: mlogm in avarage or best case. for the worst case: O(m^2). if m=n-1 => o(n^2)
//insertion sort- O(m) because the array is almost sorted. execute n-1 times => O(n*m)
//the Algorithm: O(m*n), worst case for m=n-1.
int find_k_value()
{
    int best,change;
    int *arr, *sub;
    int i,n, m, k,j,l;

    scanf("%d", &n);
    scanf("%d", &m);
    scanf("%d", &k);
    k--;
    arr = (int *)malloc(sizeof(int) * n);
    sub = (int *)malloc(sizeof(int) * m);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    for (i=0;i<n;i++)
    {
        if (i==0) // first sort for the sub array
        {
            for (j = 0; j < m; j++)
            {
                sub[j] = arr[j]; // fill the sub array
            }
            j--;
            change=arr[0];
            QuickSort(sub,0,m-1); // Quick sort the subarray
            best=sub[k];
        }
        else
        {
            l=0;
            while(change!=sub[l]) // O(m)- check the index of the element to be changed for the next window
                l++;
            sub[l]=arr[(i+j)%n]; // fill the next window-change only one number. modulo for circularity
            insertionSort(sub,m); // O(n) because the sub array is almost sorted except of one element
            if(sub[k]<best) //check if best is the smallest k element of all windows
                best=sub[k];
            change=arr[i];
        }

    }

    free(arr);
    free(sub);
    return best;
}

//Question 2: manage Transplant list
//create a Max heap- arrשט with the Patient. when we need to remove the first patient( case 4) 
//or find the k'th patient in the queue- we build the Max hea. for any other case- we work with array of patients
// complexity: worst case: n/2 insert patient to the heap array,n/2 update the last patient in the array-(n\2)^2 compartions=>
// + nlogn for worst case to find the k'th patient => O(n^2) for the worst case 
long int transplant_list()
{
    long int ans;
    int N, K, M;
    int opp;
    double TTP,age;
    long int id;
    Patient p;
    int l,index=0;
    scanf("%d", &N);
    scanf("%d", &K);
    scanf("%d", &M);
    K--;
    MaxHeap arr(N);
    for (int i=0;i<M;i++)
    {
        scanf("%d",&opp);
        switch(opp)
        { 
            case 1: // insert a new patient to the queue- O(1)
                scanf("%ld%lf%lf", &id, &age, &TTP);
                p.id=id;
                p.priority_val=(85.0-age)+(3.0/TTP);
                arr.harr[index]=p;
                index++;
                arr.heap_size=index;
                break;

            case 2: // search the patient to be changed- O(n) at the worst case
                scanf("%ld%lf%lf", &id, &age, &TTP);
                p.id=id;
                p.priority_val=(85.0-age)+(3.0/TTP);
                for(l=0;l<arr.heap_size;l++)
                {
                    if (arr.harr[l].id == p.id) // update patient and sort the heap
                    {
                        arr.harr[l].priority_val=p.priority_val;
                        break;
                    }
                }

                break;

            case 3:// remove a patient from the queue- O(n) at the worst case
                scanf("%ld", &id);
                for(int j=0;j<index;j++)
                {
                    if (arr.harr[j].id == id) // delete patient and sort the heap
                    {
                        index--;
                        if(j!=index)
                            swapPatient(arr.harr[j],arr.harr[index]);
                        arr.heap_size=index;
                        break;
                    }
                }
                break;

            case 4:// remove the first patient in the queue- O(n) at the worst case
                arr.build_max_heap();// build the max heap- O(n) at the worst case
                arr.extractMax(); // extract the first patient in the queue- O(1)
                index=arr.heap_size;
                break;


            case 5:// find the k'th patient at the queue- O(nlogn) at the worst case
                arr.build_max_heap(); // O(n)
                for(int j=0;j<K;j++) // extaract the first patient in the queue and build the heap - O(klogn), worst case:k=n
                {
                    arr.extractMax();
                    arr.MaxHeapify(0);
                }
                ans=arr.getMax();
                i=M;
                break;
        }

    }

    return ans;
}

//Question 3- sort IPs in a descending order and return the sum of the k'th ip address
// to the first number(the first number from left to right) has a weight of 256^3,the second number weight of 256^2 and so on
// Get Ips- O(n),Radix Sort:  O(d*(n+10)),while d in the worst case here is 10 => worst case: O(10n)
// sort_ip: O(10n) for the worst case- linear time sorting
int sort_ip()
{
    int ans=0;
    int num;
    int n, i, k;
    scanf("%d", &n);
    scanf("%d", &k);
    k--;
    getc(stdin);//clear enter/space
    unsigned int * ips=(unsigned int *)malloc(sizeof(unsigned int)*n);
    // get n IPs- O(n)
    for (i=0; i<n;i++)
    {
        InsertIP(ips,i);
    }
    radixsort(ips,n);
    Reverse(ips,n); // Reverse the array- sorted in descending order
// calculate each number in the k'th ip and calculate the sum of it's number
    for(i=0;i<4;i++)
    {
        switch (i)
        {
            case 0:
                num=ips[k]/(256*256*256);
                ans+=num;
                ips[k]-=num*256*256*256;
                break;
            case 1:
                num=ips[k]/(256*256);
                ans+=num;
                ips[k]-=num*256*256;
                break;
            case 2:
                num=ips[k]/256;
                ans+=num;
                ips[k]-=num*256;
                break;
            case 3:
                ans+=ips[k];
                break;
        }
    }

    free(ips);
    return ans;
}

// function to swap elements in the array
void swap (int &a,int &b)
{
    int c=a;
    a=b;
    b=c;
}

// function that take middle element in the array as pivot- places pivot element at its correct position
//and places all smaller element to the left of the pivot element
int  partition(int arr[],int low,int high)
{
    int i=low;
    int j=high;
    int pivot= arr[(high+low)/2];
    while (i<=j)
    {
        while (arr[i]<pivot)
            i++;
        while(arr[j]>pivot)
            j--;
        if(i<=j)
        {
            swap(arr[i],arr[j]);
            i++;
            j--;
        }
    }
    return i;
}


// Quick sort function with middle element as a pivot- worst case: O(n^2) as we see in the lectures
// best case: O(nlogn) as we see in the lectures
//Average case: O(nlogn) as we see in the lectures
void QuickSort(int arr[],int low,int high)
{
    int p=partition(arr,low,high);
    if(low<p-1)
        QuickSort(arr,low,p-1);
    if(p<high)
        QuickSort(arr,p,high);
}


// get Ip and calclulate the weight of each number- O(1)
void InsertIP(unsigned int arr[],int j)
{
    int ch;
    unsigned int x;
    unsigned char str[4];
    //get new IP from user
    for (int i = 0; i < 4; i++) {
        str[i] = 0;
        while (1) {
            ch = getc(stdin);
            if (ch == '.' || ch == ' ' || ch == '\n' || ch == EOF)
                break;
            str[i] *= 10;
            str[i] += ch - '0';
        }
        //    sscanf(str,"%d",x);
        x=str[i];
        switch (i)
        {
            case 0:
                arr[j]=256*256*256*x;
                break;
            case 1:
                arr[j]+=256*256*x;
                break;
            case 2:
                arr[j]+=256*x;
                break;
            case 3:
                arr[j]+=x;
                break;
        }
    }//for i=1:4
}
// function which Reverse the arr ( for Quick sort in Descending order)- n/2 swaps => O(n)
void Reverse(unsigned int arr[],int size)
{
    for(int i=0,j=size-1;i<size/2;i++,j--)
    {
        swap(arr[i],arr[j]);
    }
    return;
}
// function to find the max value in the array- O(n)
unsigned int getMax(unsigned int arr[], int n)
{
    unsigned int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(unsigned int arr[], int n, unsigned long long  exp)
{
    unsigned int * output=(unsigned int *)malloc(sizeof(unsigned int)*n);
    int i, count[10] = { 0 };

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using
// Radix Sort- O(d*(n+10)) while d is the number of digits in the largest number and 10 is the base we work with
void radixsort(unsigned int arr[], int n)
{
    // Find the maximum number to know number of digits
    unsigned int m = getMax(arr, n);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (unsigned long long exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

// Insertion sort- average and worst case: O(n^2), best case(when the array is almost sorted)- O(n)
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Constructor: Builds a heap from a given array a[] of given size
MaxHeap::MaxHeap(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = (Patient*)malloc(sizeof(Patient) * (cap+1));
}



// Method to remove Max element (or root) from Max heap
//O(1)
void MaxHeap::extractMax()
{
    //  remove the max value from heap
    heap_size--;
    swapPatient(harr[0],harr[heap_size]);

}


// A recursive method to heapify a subtree with the root at given index
// O(logn) at the worst case
void MaxHeap::MaxHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int largest=i;

    if (l < heap_size && harr[l].priority_val > harr[largest].priority_val)
        largest = l;
    else
        largest=i;

    if (r < heap_size && harr[r].priority_val > harr[largest].priority_val)
        largest = r;
    if (largest != i)
    {
        swapPatient(harr[i], harr[largest]);
        MaxHeapify(largest);
    }
}

// function to swap elements in the array
void swapPatient (Patient &a,Patient &b)
{
    Patient c=a;
    a=b;
    b=c;
}
//function to build a Max Heap
// O(n)- as we saw at the lecture
void MaxHeap:: build_max_heap()
{
    int i;
    for(i=heap_size/2-1;i>=0;i--)
        MaxHeapify(i);
}