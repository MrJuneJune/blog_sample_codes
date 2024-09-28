
#include <memory>

class Node {
 public:
  Node* next;
  Node* prev;
  int val;

  explicit Node(int val) : val(val), next(nullptr), prev(nullptr) {}
};

class MyCircularDeque {
 public:
  int sizes;
  int curr_size;
  Node* head;
  Node* tail;

  explicit MyCircularDeque(int k) : sizes(k), curr_size(0) {
    head = new Node(-1);
    tail = new Node(-1);

    head->next = tail;
    head->prev = tail;
    tail->next = head;
    tail->prev = head;
  }

  bool insertFront(int value) {
    if (isFull())
      return false;
    _insert(head, new Node(value));
    return true;
  }

  bool insertLast(int value) {
    if (isFull())
      return false;
    _insert(tail->prev, new Node(value));
    return true;
  }

  bool deleteFront() {
    if (isEmpty())
      return false;
    _delete(head->next);
    return true;
  }

  bool deleteLast() {
    if (isEmpty())
      return false;
    _delete(tail->prev);
    return true;
  }

  int getFront() { return head->next->val; }

  int getRear() { return tail->prev->val; }

  bool isEmpty() { return head->next == tail; }

  bool isFull() { return curr_size == sizes; }

 private:
  void _insert(Node* node1, Node* node2) {
    // linking new node
    node2->next = node1->next;
    node2->prev = node1;
    // linking next node to new node
    node1->next->prev = node2;
    // linking prev node to new node
    node1->next = node2;

    curr_size += 1;
  }

  void _delete(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;

    curr_size -= 1;
  }
};
