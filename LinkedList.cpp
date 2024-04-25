#include <memory>
#include <vector>
#include <iostream>


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