#include <iostream>

class MyString {
private:
	char* buffer;
	size_t length;
public:
	MyString(const char* str) {
		length = strlen(str);
		buffer = new char[length + 1];
		strcpy_s(buffer, length + 1, str);
		buffer[length] = '\0';
	}
	~MyString() {
		delete[] buffer;
	}
	MyString(const MyString& other) { //copy constructor
		length = other.length;
		buffer = new char[length + 1];
		strcpy_s(buffer, length + 1, other.buffer);
	}
	MyString& operator=(const MyString& other) { //copy assignment operator
		if (this != &other) {
			delete[] buffer; // free existing resource
			length = other.length;
			buffer = new char[length + 1];
			strcpy_s(buffer, length + 1, other.buffer);
		}
		return *this;
	}
	MyString operator+(const MyString& other) { //concatenation operator
		size_t newlen = length + other.length;
		char* newbuffer = new char[newlen + 1];
		strcpy_s(newbuffer, length + 1, buffer);
		strcat_s(newbuffer, newlen + 1, other.buffer);
		MyString result(newbuffer);
		delete[] newbuffer; // clean up temporary buffer
		return result;
	}
	bool operator==(const MyString& other) const { //equality operator
		return strcmp(buffer, other.buffer) == 0;
	}
	void print() const {
		std::cout << buffer;
	}
};

int main() {
	std::cout << "--- Testing Constructors ---" << std::endl;
	MyString s1("Hello");
	MyString s2("World");
	s1.print();
	std::cout << std::endl;
	s2.print();
	std::cout << std::endl;

	std::cout << "\n--- Testing Concatenation (+) ---" << std::endl;
	MyString s3 = s1 + MyString(" ") + s2;
	s3.print();
	std::cout << std::endl;

	std::cout << "\n--- Testing Rule of Three ---" << std::endl;
	MyString s4 = s3; // Tests Copy Constructor
	MyString s5("Temp");
	s5 = s1;          // Tests Copy Assignment Operator

	s4.print();
	std::cout << std::endl;
	s5.print();
	std::cout << std::endl;

	std::cout << "\n--- Testing Equality (==) ---" << std::endl;
	if (s1 == s5) {
		std::cout << "Success: s1 and s5 are equal!" << std::endl;
	}
	if (!(s1 == s2)) {
		std::cout << "Success: s1 and s2 are NOT equal!" << std::endl;
	}

	return 0; // If destructors are wrong, the program will crash right here!
}