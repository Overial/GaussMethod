// IDB-19-07
// Afanasyev Vadim
// Gauss Method

#include <iostream>
#include <ctime>

using namespace std;

void my_allocate_matr(int**& matr, int iRowCount, int iColCount) {
	matr = new int* [iRowCount];
	for (int i = 0; i < iRowCount; i++) {
		matr[i] = new int[iColCount];
	}
}

void my_delete_matr(int**& matr, int iRowCount) {
	for (int i = 0; i < iRowCount; i++) {
		delete[] matr[i];
	}
	delete[] matr;
}

void my_fill_matr_random(int**& matr, int iRowCount, int iColCount, int iLowerBound, int iUpperBound) {
	for (int i = 0; i < iRowCount; i++) {
		for (int j = 0; j < iColCount; j++) {
			matr[i][j] = iLowerBound + rand() % (iUpperBound - iLowerBound + 1);
		}
	}
}

void my_print_matr(int**& matr, int iRowCount, int iColCount) {
	for (int i = 0; i < iRowCount; i++) {
		for (int j = 0; j < iColCount; j++) {
			cout << matr[i][j] << "|";

			if (j == iColCount - 1) {
				cout << '\n';
			}
		}
	}
}

int main() {
	{
		// srand(static_cast<unsigned int>(time(NULL)));

		int iRowCount = 0;
		int iColCount = 0;
		cout << "Enter the amount of the rows: ";
		cin >> iRowCount;
		cout << "Enter the amount of the cols: ";
		cin >> iColCount;

		int iLowerBound = 0;
		int iUpperBound = 0;
		cout << "Enter the lower bound: ";
		cin >> iLowerBound;
		cout << "Enter the upper bound: ";
		cin >> iUpperBound;

		int** matr = nullptr;
		my_allocate_matr(matr, iRowCount, iColCount);
		my_fill_matr_random(matr, iRowCount, iColCount, iLowerBound, iUpperBound);
		my_print_matr(matr, iRowCount, iColCount);
		my_delete_matr(matr, iRowCount);
	}

	_CrtDumpMemoryLeaks();

	return 0;
}
