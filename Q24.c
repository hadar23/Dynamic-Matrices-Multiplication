#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define INFY 999999999
// int m[20][20];
// int s[20][20];
// int p[20], i, j, n;

int n; // number of matrices
int* m; // matrix: minimum computations. size n*n
int* s; // matrix: where to cut the list of matrices. size n*n
int* p; // list: sizes vector of the matrices. size n+1

void printOptimal(int i, int j);
int MatrixChainOrderMin(int i, int j);
void matrixMultiplyCheck();

int main(int argc, char** argv) {
	int i, j, k;
	printf("Enter the no. of elements: ");
	scanf("%d", &n);
	// ready for checking
	/*////////////////////////////
	 n = 6;
	 ////////////////////////////*/
	// dynamic alocation
	m = (int*) calloc((n + 1) * (n + 1), sizeof(int));
	s = (int*) calloc((n + 1) * (n + 1), sizeof(int));
	p = (int*) calloc(n + 1, sizeof(int));

	// reset matrices S and M
	for (i = 1; i <= n; i++) {
		for (j = i + 1; j <= n; j++) {
			*(m + i * (n + 1) + i) = 0;
			*(m + i * (n + 1) + j) = INFY;
			*(s + i * (n + 1) + j) = 0;
		}
	}

	// reset list P
	printf("\nEnter the dimensions: \n");
	for (k = 0; k <= n; k++) {
		printf("P%d: ", k);
		scanf("%d", &p[k]);
	}

	// ready for checking
	/*////////////////////////////////////////
	 p[0] = 30;
	 p[1] = 35;
	 p[2] = 15;
	 p[3] = 5;
	 p[4] = 10;
	 p[5] = 20;
	 p[6] = 25;
	 /////////////////////////////////////////*/

	matrixMultiplyCheck();

	printf("\nMatrix M:\n");
	for (i = 1; i <= n; i++) {
		for (j = i; j <= n; j++)
			printf("m[%d][%d]: %d\t", i, j, *(m + i * (n + 1) + j));
		printf("\n");
	}

	printf("\nMatrix S:\n");
	for (i = 1; i <= n; i++) {
		for (j = i; j <= n; j++)
			printf("s[%d][%d]: %d\t", i, j, *(s + i * (n + 1) + j));
		printf("\n");
	}

	i = 1, j = n;
	printf("\nMultiplication Sequence: ");
	printOptimal(i, j);
	printf("\nMinimum number of multiplications is: %d",
			MatrixChainOrderMin(1, n));

	free(m);
	free(s);
	free(p);

	return 0;
}

// print the s matrix
void printOptimal(int i, int j) {
	if (i == j)
		printf(" A%d ", i);
	else {
		printf("( ");
		printOptimal(i, *(s + (i * (n + 1)) + j));
		printOptimal(*(s + (i * (n + 1)) + j) + 1, j);
		printf(" )");
	}
}

// multiply the matrices
void matrixMultiplyCheck() {
	long int q;
	int k, i, j;
	for (i = n; i > 0; i--) {
		for (j = i; j <= n; j++) {
			if (i == j)
				*(m + i * (n + 1) + j) = 0;
			else {
				for (k = i; k < j; k++) {
					q = *(m + i * (n + 1) + k) + *(m + (k + 1) * (n + 1) + j)
							+ p[i - 1] * p[k] * p[j];
					if (q < *(m + i * (n + 1) + j)) {
						*(m + i * (n + 1) + j) = q;
						*(s + i * (n + 1) + j) = k;
					}
				}
			}
		}
	}
}

// find the minimum recursively
int MatrixChainOrderMin(int i, int j) {
	if (i == j)
		return 0;
	int k;
	int min = INT_MAX;
	int count;

	for (k = i; k < j; k++) {
		count = MatrixChainOrderMin(i, k) + MatrixChainOrderMin(k + 1, j)
				+ p[i - 1] * p[k] * p[j];
		if (count < min)
			min = count;
	}
	// Return minimum count
	return min;
}

