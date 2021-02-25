// IDB-19-07
// Afanasyev Vadim
// Gauss Method

#include <iostream>
#include <iomanip>

using namespace std;

void my_allocate_matr(float**& matr, int iRowCount, int iColCount) {
	matr = new float* [iRowCount];
	for (int i = 0; i < iRowCount; i++) {
		matr[i] = new float[iColCount];
	}
}

void my_delete_matr(float**& matr, int iRowCount) {
	for (int i = 0; i < iRowCount; i++) {
		delete[] matr[i];
	}
	delete[] matr;
}

void my_fill_matr_input(float**& matr, int iRowCount, int iColCount) {
	for (int i = 0; i < iRowCount; i++) {
		for (int j = 0; j < iColCount; j++) {
			cout << "Enter [" << i << "][" << j << "] element: ";
			cin >> matr[i][j];
		}
	}
}

void my_print_matr(float**& matr, int iRowCount, int iColCount) {
	for (int i = 0; i < iRowCount; i++) {
		for (int j = 0; j < iColCount; j++) {
			cout << setprecision(3) << matr[i][j] << "|";
		}
		cout << '\n';
	}
}

void my_gauss_method(float**& matr, int iRowCount, int iColCount) {
	// Find pivot element
	for (int i = 0; i < iRowCount; i++) {
		for (int k = i + 1; k < iRowCount; k++) {
			if (abs(matr[i][i]) < abs(matr[k][i])) {
				for (int j = 0; j < iColCount; j++) {
					float iTemp1 = matr[i][j];
					matr[i][j] = matr[k][j];
					matr[k][j] = iTemp1;
				}
			}
		}
	}

	// Make pivot element equal to one
	for (int j = 0; j < iColCount; j++) {
		matr[0][j] /= matr[0][0];
	}

	// Make column elements below pivot element equal to zero
	for (int i = 0; i < iRowCount - 1; i++) {
		for (int k = i + 1; k < iRowCount; k++) {
			float iFactor = matr[k][i] / matr[i][i];
			for (int j = 0; j < iColCount; j++) {
				matr[k][j] -= iFactor * matr[i][j];
			}
		}
	}

	// Back-substitution
	float* x = new float[iRowCount];
	for (int i = 0; i < iRowCount; i++) {
		x[i] = matr[i][iColCount - 1];
	}
	for (int i = iRowCount - 1; i >= 0; i--) {
		for (int k = i; k < iRowCount; k++) {
			if (k != i) {
				x[i] -= matr[i][k] * x[k];
			}
		}
	}

	// Print result
	cout << "\nThe required values:\n";
	cout << '( ';
	for (int i = 0; i < iRowCount; i++) {
		cout << fixed << setprecision(1) << x[i] << ', ';
	}
	cout << ')';
	delete[] x;
}

int main() {
	{
		int iRowCount = 0;
		int iColCount = 0;
		cout << "Enter the amount of the rows: ";
		cin >> iRowCount;
		cout << "Enter the amount of the columns: ";
		cin >> iColCount;

		float** matr = nullptr;
		my_allocate_matr(matr, iRowCount, iColCount);
		my_fill_matr_input(matr, iRowCount, iColCount);
		my_print_matr(matr, iRowCount, iColCount);
		my_gauss_method(matr, iRowCount, iColCount);
		my_delete_matr(matr, iRowCount);
	}

	_CrtDumpMemoryLeaks();

	return 0;
}
