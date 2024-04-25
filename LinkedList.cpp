#include <memory>
#include <vector>
#include <iostream>

template<typename T>
class Node {
public: 
	Node(T);
	Node() {};
	void insert(const std::vector<T>&);
	void display();
	int length();
	bool exists(T);
	void reverse();
	void insert_at(int, T);
	int delete_first();
	int delete_at(T);
	void insert_before_first(T);

private:
	std::shared_ptr<Node> head, last, prev, next;
	int data = 0;
};

template<typename T>
bool
Node<T>::exists(T data) {
	auto p = head;
	while (p) {
		if (p->data == data) return true;
		p = p->next;
	}
	return false;
}


template<typename T>
void
Node<T>::reverse() {
	auto p = head;

	while (p) {
		auto temp = p->next;
		p->next = p->prev;
		p->prev = temp;
		p = p->prev;
		// last node?
		if (!p && !p->next) {
			head = p;
		}
	}
}

template<typename T>
int
Node<T>::delete_at(T pos) {
	if (pos >= length()) {
		throw std::runtime_error{ "Wrong len" };
	}
	auto p = head;

	// advance to pos
	for (int i = 0; i < pos - 1; i++) {
		p = p->next;
	}
	p->prev->next = p->next;

	//any nodes after this one? 
	if (p->next) {
		p->next->prev = p->prev;
	}
	auto x = p->data;
	p.reset();
	return x;
}

template<typename T>
int
Node<T>::delete_first() {
	auto p = head;
	head = head->next;
	if (head) {
		head->prev.reset();
	}
	return p->data;
}

template<typename T>
void
Node<T>::insert_at(int pos, T d) {
	if (pos >= length()) {
		throw std::runtime_error{"Wrong position"};
	}

	if (pos == 0) {
		insert_before_first(d);
		return;
	}

	auto t = std::make_shared<Node>();
	t->data = d;

	// advance to pos
	auto p = head;
	for (auto i = 0; i < pos- 1; i++) {
		p = p->next;
	}
	t->next = p->next;
	t->prev = p;
	if (p->next) {
		p->next->prev = t;
	}
	p->next = t;
}

template<typename T>
void
Node<T>::insert_before_first(T data) {
	auto t = std::make_shared<Node>();
	t->data = data;
	t->next = head;
	head->prev = t;
	head = t;
}

template<typename T>
int
Node<T>::length() {
	int len = 0;
	auto p = head;
	while (p) {
		len++;
		p = p->next;
	}
	return len;
}

template<typename T>
Node<T>::Node(T data) {
	this->data = data;
	head = std::make_shared<Node>();
}

template<typename T>
void
Node<T>::display() {
	auto p = head;
	while (p) {
		std::cout << p->data << '\t';
		p = p->next;
	}
	std::cout << std::endl;
}

template<typename T>
void
Node<T>::insert(const std::vector<T>& v) {
	last = head;
	for (auto val : v) {
		auto t = std::make_shared<Node>();
		t->data = val;
		t->next = last->next;
		t->prev = last;
		last->next = t;
		last = t;
	}
}

int main() {
	Node<int>* n = new Node<int>(4);
	std::vector<int> v{ 1,2,3,4,5,6 };
	n->insert(v);
	n->insert_before_first(-7);
	n->insert_at(4, 200);
	n->display();
	n->delete_first();
	n->delete_at(2);
	n->display();
	return 0;
}