#include <memory>
#include <vector>
#include <iostream>

class Node {
public: 
	Node(int);
	Node() {};
	void insert(const std::vector<int>&);
	void display();
	int length();
	void insert_at(int, int);
	int delete_first();
	int delete_at(int);
	void insert_before_first(int data);

private:
	std::shared_ptr<Node> head, last, prev, next;
	int data = 0;
};

int
Node::delete_at(int pos) {
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


int
Node::delete_first() {
	auto p = head;
	head = head->next;
	if (head) {
		head->prev.reset();
	}
	return p->data;
}

void
Node::insert_at(int pos, int d) {
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

void
Node::insert_before_first(int data) {
	auto t = std::make_shared<Node>();
	t->data = data;
	t->next = head;
	head->prev = t;
	head = t;
}

int
Node::length() {
	int len = 0;
	auto p = head;
	while (p) {
		len++;
		p = p->next;
	}
	return len;
}

Node::Node(int data) {
	this->data = data;
	head = std::make_shared<Node>();
}

void
Node::display() {
	auto p = head;
	while (p) {
		std::cout << p->data << '\t';
		p = p->next;
	}
	std::cout << std::endl;
}

void
Node::insert(const std::vector<int>& v) {
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
	Node* n = new Node(4);
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