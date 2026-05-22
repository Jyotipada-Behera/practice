#include <iostream>

class Matrix {
private:
	int rows;
	int cols;
	int** data;
	int checkBounds(int r, int c) const {
		if (r < 0 || r >= this->rows || c < 0 || c >= this->cols)
			throw std::out_of_range("Index out of bounds");
		return 0;
	};
public:
	Matrix(int r, int c) {
		this->rows=r;
		this->cols=c;
		this->data=new int*[r];
		for(int i=0; i<r; i++)
			this->data[i]=new int[c](0);
	};
	~Matrix() {
		for(int i=0; i<this->rows; i++)
			delete[] this->data[i];
		delete[] this->data;
	};
	int getValue(int r, int c) const {
		try {
			this->checkBounds(r, c);
		} catch (const std::out_of_range& e) {
			std::cout << "Exception caught: " << e.what() << std::endl;
			return -1;
		}
		return this->data[r][c];
	};
	void setValue(int r, int c, int value) {
		try {
			this->checkBounds(r, c);
		} catch (const std::out_of_range& e) {
			std::cout << "Exception caught: " << e.what() << std::endl;
			return;
		}
		this->data[r][c]=value;
	};
	void display() const {
		std::cout << "--- Matrix (3x3) ---" << std::endl;
		for (int i = 0; i < this->rows; i++) {
			for (int j = 0; j < this->cols; j++)
				std::cout << this->data[i][j] << " ";
			std::cout << std::endl;
		}
	};
};

int main() {
	std::cout << "--- Lightweight matrix math library ---" << std::endl;

	// Create a 3x3 matrix
	Matrix mat(3, 3);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			mat.setValue(i, j, i * j);

	mat.display();

	std::cout << "--- Testing Bounds ---" << std::endl;
	mat.setValue(5, 0, 10); // Out of bounds

	return 0;
}