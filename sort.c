//-----------------------------------------------------------------------------
// Sort.c
//
// compile: gcc -std=c99 -o Sort Sort.c
//
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>

void printArray(int* Arr, int max){
   int i;
   for(i=0; i<max; i++){
      printf("%d ", A[i]);
   }
   printf("\n");
}

void swap(int* Arr, int i, int j){
   int temp;
   temp = Arr[i];
   Arr[i] = Arr[j];
   Arr[j] = temp;
}

void BubbleSort(int* Arr, int max){
   int i, j;
   for(j=max-1; j>0; j--){
      for(i=1; i<=j; i++){
         if( Arr[i]<Arr[i-1] ){
            swap(Arr, i, i-1);
         }
      }
   }
}

void SelectionSort(int* Arr, int n){
   int i, j, imax;
   for(j=n-1; j>0; j--){
      imax = 0;
      for(i=1; i<=j; i++){
         if( Arr[imax]<Arr[i] ){
            imax = i;
         }
      }
      swap(Arr, imax, j);
   }
}

void InsertionSort(int* Arr, int n){
   int i, j, temp;
   for(j=1; j<n; j++){
      temp = Arr[j];
      i = j-1;
      while( i>=0 && temp<Arr[i] ){
         Arr[i+1] = Arr[i];
         i--;
      }
      Arr[i+1] = temp;
   }
}

void Merge(int* A, int p, int q, int r){
   int i, j, k, n1=q-p+1, n2=r-q;
   int* L = calloc(n1, sizeof(int));
   int* R = calloc(n2, sizeof(int));
   assert(L!=NULL && R!=NULL);

   for(i=0; i<n1; i++) L[i] = A[p+i];
   for(j=0; j<n2; j++) R[j] = A[q+j+1];
   i = 0; j = 0;
   for(k=p; k<=r; k++){
      if( i<n1 && j<n2 ){
         if( L[i]<R[j] ){ A[k] = L[i]; i++;}
         else{ A[k] = R[j]; j++;}
      }
      else if( i<n1 ){ A[k] = L[i]; i++;}
      else{ /* j<n2 */ A[k] = R[j]; j++;}
   }
   free(L);
   free(R);
}

void MergeSort(int* A, int p, int r){
   int q;
   if( p<r ){
      q = (p+r)/2;
      MergeSort(A, p, q);
      MergeSort(A, q+1, r);
      Merge(A, p, q, r);
   }
}

int Partition(int* A, int p, int r){
   int i, j, x;
   x = A[r];
   i = p-1;
   for(j=p; j<r; j++){
      if( A[j]<=x ){
         i++;
         swap(A, i, j);
      }
   }
   swap(A, i+1, r);
   return(i+1);
}

void QuickSort(int* A, int p, int r){
   int q;
   if( p<r ){
      q = Partition(A, p, r);
      QuickSort(A, p, q-1);
      QuickSort(A, q+1, r);
   }
}

void CountingSort(int* A, int n, int k){
   int i, j;
   int* C = calloc(k+1, sizeof(int));
   int* B = calloc(n, sizeof(int));  // output array
   assert(C!=NULL);

   // initialize C[] to all zeros
   // not really necessary since calloc zeros the array
   for(i=0; i<=k; i++){  
      C[i] = 0;
   }

   // set C[i] to #elements in A[] that are equal to i
   for(j=0; j<n; j++){
      C[A[j]]++;
   }

   // set C[i] to #elements in A[] that are less than or equal to i
   for(i=1; i<=k; i++){
      C[i] += C[i-1];
   }

   // place elements of A[] into their proper positions in B[]
   for(j=n-1; j>=0; j--){
      B[C[A[j]]-1] = A[j];
      C[A[j]]--;
   }

   // copy elements of B[] into original array A[], in order
   for(j=0; j<n; j++){
      A[j] = B[j];
   }

   // free heap memory
   free(B);
   free(C);
}

// RadixSort()
// pre: A[] contains only positive integers
void RadixSort(int* A, int n){
   int i, j, m, d, a;
   int** D; // D[i][j] = digit i of A[j]

   // find maximum element in A[]
   m = A[0];
   for(i=1; i<n; i++) if( A[i]>m ) m = A[i];

   // find number of decimal digits in m
   d = (int)log10(m);

   // allocate space for D[][]
   D = calloc(d, sizeof(int*));
   for(i=0; i<d; i++) D[i] = calloc(n, sizeof(int));

   // transform A[] into a 2-dim array of decimal digits D[][]
   for(j=0; j<n; j++){
      a = A[j];
      for(i=0; i<d; i++){
         D[i][j] = a%10;
         a /= 10;
      }
   }

   // perform Radix Sort algorithm on array D[][]
   for(i=0; i<d; i++){
      CountingSort(D[i], n, 9);
   }

   // transform elements of D[][] back into A[]
   for(j=0; j<n; j++){
      a = D[d-1][j];
      for(i=d-2; i>=0; i++){
         a *= 10;
         a += D[i][j];
      }
      A[j] = a;
   }

}

int main(int argc, char** argv){
   int i, n=9;
   int A[] = {9,5,3,6,7,4,8,1,2};

   printArray(A, n);

   //BubbleSort(A, n);
   //SelectionSort(A, n);
   //InsertionSort(A, n);
   //MergeSort(A, 0, n-1);
   //QuickSort(A, 0, n-1)
   //CountingSort(A, n, 9);
   RadixSort(A, n);

   printArray(A, n);

   return(EXIT_SUCCESS);
}
