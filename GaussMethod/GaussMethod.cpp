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
	cout << '\n';
	for (int i = 0; i < iRowCount; i++) {
		for (int j = 0; j < iColCount; j++) {
			cout << setw(4) << setprecision(5) << matr[i][j] << "|";
		}
		cout << '\n';
	}
}

void my_gauss_method(float**& matr, int iRowCount, int iColCount) {
	// Make first element equal to one
	float fTemp1 = matr[0][0];
	for (int j = 0; j < iColCount; j++) {
		matr[0][j] /= fTemp1;
	}
	my_print_matr(matr, iRowCount, iColCount);

	// Make column elements below first element equal to zero
	for (int i = 0; i < iRowCount - 1; i++) {
		for (int k = i + 1; k < iRowCount; k++) {
			float iFactor = matr[k][i] / matr[i][i];
			for (int j = 0; j < iColCount; j++) {
				matr[k][j] -= iFactor * matr[i][j];
			}
		}
	}
	for (int i = 0; i < iRowCount; i++) {
		for (int j = 0; j < i; j++) {
			// Make column elements below first element equal to zero explicitly
			matr[i][j] = NULL;
		}
	}
	my_print_matr(matr, iRowCount, iColCount);

	// Make main diagonal elements equal to one
	for (int i = 0; i < iRowCount; i++) {
		float fTemp2 = matr[i][i];
		for (int j = 0; j < iColCount; j++) {
			matr[i][j] /= fTemp2;
		}
	}
	my_print_matr(matr, iRowCount, iColCount);

	// Back-substitution
	float* x = new float[iRowCount];
	for (int i = 0; i < iRowCount; i++) {
		x[i] = matr[i][iColCount - 1];
	}
	for (int i = iRowCount - 2; i >= 0; i--) {
		for (int j = i + 1; j < iRowCount; j++) {
			x[i] -= matr[i][j] * x[j];
		}
	}

	// Print result
	cout << "\nThe required values:\n\n";
	for (int i = 0; i < iRowCount; i++) {
		cout << x[i] << "|";
	}
	cout << '\n';
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
