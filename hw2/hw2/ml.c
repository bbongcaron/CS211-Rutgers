/*
 *
 * This code calculates the house price of a house by learing from
 * training data. It uses pseudo inverse of a given matrix to find the
 * weight of different features.
 *
 * Predicted Price : Y = W0 + W1*x1 + W2*X2 + W3*X3 + W4*X4
 * Weight Matrix : W = pseudoInv(X)*Y
 * pseudoInv(X) = inverse(transpose(X)*X) * transpose(X)
 *
 * weight(w) = pseudoInv(X) * Y
 * 			where	X = Input data matrix
 * 					Y = Target vector
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
// all methods declarations
double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2);
double** transposeMatrix(double** mat, int row, int col);
double** inverseMatrix(double **matA, int dimension);
void freeMatrix(double** matrix, int row);
void printMatrix(double** matrix, int row, int col);

// main method starts here
int main(int argc, char* argv[argc+1]){

    // your code goes here
	FILE* train_file = fopen(argv[1], "r");
  int k_train;
  int n_train;
  fscanf(train_file, "%d\n", &k_train);
  fscanf(train_file, "%d\n", &n_train);
  double** x = malloc(n_train*sizeof(double*));
  double** y = malloc(n_train*sizeof(double*));
  for (int i = 0; i < n_train; i++)
  {
    // initialize each row with k_train + 1 columns
    x[i] = malloc((k_train + 1)*sizeof(double));
		// initialize each row with 1 column
		y[i] = malloc(sizeof(double));
    // Element i,0 is always 1
    x[i][0] = 1;
    // Fill row i with attributes from training data file
    for (int j = 1; j < k_train + 1; j++)
    {
      fscanf(train_file, "%lf,", &x[i][j]);
    }
    // Matrix y contains the prices of the houses
    // In the training data, it is the last number in each row
    fscanf(train_file, "%lf\n", &y[i][0]);
  }

	double** xTran = transposeMatrix(x, n_train, k_train + 1);

	// multiplyMatrix result will have k_train + 1 rows
	double** xTy = multiplyMatrix(xTran, y, k_train + 1, n_train, n_train, 1);

	double** xTx = multiplyMatrix(xTran, x, k_train + 1, n_train, n_train, k_train + 1);
	double** inverse = inverseMatrix(xTx, k_train + 1);

	double** weights = multiplyMatrix(inverse, xTy, k_train + 1, k_train + 1, k_train + 1, 1);

  // Free Matrices EXCEPT weights
	freeMatrix(xTx, k_train + 1);
	freeMatrix(x, n_train);
	freeMatrix(xTran, k_train + 1);
  freeMatrix(y, n_train);
	freeMatrix(inverse, k_train + 1);
	freeMatrix(xTy, k_train + 1);
	fclose(train_file);

  FILE* test_file = fopen(argv[2], "r");
	int m_test;
	fscanf(test_file, "%d\n", &m_test);
	double** xprime = malloc(m_test*sizeof(double*));
	for (int i = 0; i < m_test; i++)
	{
		xprime[i] = malloc((k_train + 1)*sizeof(double));
		xprime[i][0] = 1;
	}

	for (int i = 0; i < m_test; i++){
		// last data element will be in form %lf\n, so go to k_train only in loop
		for (int j = 1; j < k_train; j++)
		{
			fscanf(test_file, "%lf,", &xprime[i][j]);
		}
		fscanf(test_file, "%lf\n", &xprime[i][k_train]);
	}
	double** prices = multiplyMatrix(xprime, weights, m_test, k_train + 1, k_train + 1, 1);

	printMatrix(prices, m_test, 1);
	freeMatrix(weights, k_train + 1);
	freeMatrix(prices, m_test);
	fclose(test_file);
	return 0;
}

void freeMatrix(double** matrix, int row)
{
	for (int i = 0; i < row; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
}

void printMatrix(double** matrix, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			printf("%d\t", (int)matrix[i][j]);
		}
		printf("\n");
	}
}

double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2)
{
	double** result=malloc(r1*sizeof(double*));
	assert(r2 == c1);
	for(int i = 0; i < r1; i++)
	{
		result[i] = calloc(c2,sizeof(double));
	}
	// r1 = r3
	// c1 = r2
	// c2 = c3
	for (int i = 0; i < r1; i++)
	{
		for (int j = 0; j < c2; j++)
		{
			for (int k = 0; k < c1; k++)
			{
				result[i][j] += matA[i][k]*matB[k][j];
			}
		}
	}
	return result;
}

double** transposeMatrix(double** mat, int row, int col)
{
	double** matTran=malloc(col*sizeof(double*));
	for (int i = 0; i < col; i++)
	{
		matTran[i] = malloc(row*sizeof(double));
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			matTran[j][i] = mat[i][j];
		}
	}
  return matTran;
}


double** inverseMatrix(double **matA, int dimension)
{
	// matI starts off as an n by n identity matrix
  double** matI=malloc(dimension*sizeof(double*));
	for (int i = 0; i < dimension; i++)
	{
		matI[i] = calloc(dimension,sizeof(double));
		matI[i][i] = 1;
	}

	for (int p = 0; p < dimension; p++)
	{
		double f = matA[p][p];
		// divide Mp and Np by f
		for (int i = 0; i < dimension; i++)
		{
			matA[p][i] /= f;
			matI[p][i] /= f;
		}
		for (int i = p + 1; i < dimension; i++)
		{
			f = matA[i][p];
			// subtract Mp x f from Mi AND subtract Np x f from Ni
			for (int j = 0; j < dimension; j++)
			{
				matA[i][j] -= matA[p][j]*f;
				matI[i][j] -= matI[p][j]*f;
			}
		}
	}

	for (int p = dimension - 1; p >= 0; p--)
	{
		for (int i = p - 1; i >= 0; i--)
		{
			double f = matA[i][p];
			for (int j = 0; j < dimension; j++)
			{
				matA[i][j] -= matA[p][j]*f;
				matI[i][j] -= matI[p][j]*f;
			}
		}
	}
	return matI;
}
