#include <iostream>
#include <stdexcept>

template <typename T>
struct Node {
	T data;
	Node* next;
	Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {

private:
	Node<T>* head;

public:
	LinkedList() : head(nullptr) {}
	~LinkedList() {
		while (head != nullptr) {
			Node<T>* temp = head;
			head = head->next;
			delete temp;
		}
	}
	void push_front(T value) {
		Node<T>* newNode = new Node<T>(value);
		newNode->next = head;
		head = newNode;
	}
	void pop_front() {
		Node<T>* temp = head;
		if (temp == nullptr) {
			throw std::underflow_error("List is empty.");
		}
		head = head->next;
		delete temp;
	}
	void display() const {
		Node<T>* temp = head;
		while (temp != nullptr) {
			std::cout << "[" << temp->data << "]" << " -> ";
			temp = temp->next;
		}
		std::cout << "nullptr" << std::endl;
	}
	void reverse() {
		Node<T>* prev = nullptr;
		Node<T>* current = head;
		Node<T>* next = nullptr;
		while (current != nullptr) {
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}
		head = prev;
	}
};

int main() {
	LinkedList<int> list;
	list.push_front(10);
	list.push_front(20);
	list.push_front(30);

	std::cout << "--- Initial List ---" << std::endl;
	list.display();

	std::cout << "--- Reversed List ---" << std::endl;
	list.reverse();
	list.display();

	std::cout << "--- Testing Pop ---" << std::endl;
	while (true) {
		try {
			list.pop_front();
		}
		catch (const std::underflow_error& e) {
			std::cout << "Popped all items." << std::endl;
			std::cout << "Exception caught: " << e.what() << std::endl;
			break;
		}
		list.display();
	}
}