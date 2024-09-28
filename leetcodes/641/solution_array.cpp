class MyCircularDeque {
 public:
  int size;
  int front;
  int rear;
  int* arr;

  explicit MyCircularDeque(int k) : size(k) {
    arr = new int[k];
    front = rear = -1;
  }

  bool insertFront(int value) {
    if (isFull()) {
      return false;
    } else if (front == -1) {
      front = rear = 0;
    } else if (front == 0 && rear != size - 1) {
      front = size - 1;
    } else {
      front--;
    }
    arr[front] = value;
    return true;
  }

  bool insertLast(int value) {
    if (isFull()) {
      return false;
    } else if (front == -1) {
      front = rear = 0;
    } else if ((rear == size - 1) && (front != 0)) {
      rear = 0;
    } else {
      rear++;
    }
    arr[rear] = value;
    return true;
  }

  bool deleteFront() {
    if (front == -1) {
      return false;
    } else if (front == rear) {
      front = rear = -1;
    } else if (front == size - 1) {
      front = 0;
    } else {
      front++;
    }
    return true;
  }

  bool deleteLast() {
    if (front == -1) {
      return false;
    } else if (front == rear) {
      front = rear = -1;
    } else if (rear == 0) {
      rear = size - 1;
    } else {
      rear--;
    }
    return true;
  }

  int getFront() {
    if (isEmpty()) {
      return -1;
    }
    return arr[front];
  }

  int getRear() {
    if (isEmpty()) {
      return -1;
    }
    return arr[rear];
  }

  bool isEmpty() {
    if (front == -1) {
      return true;
    } else {
      return false;
    }
  }

  bool isFull() {
    return (front == 0 && rear == size - 1) ||
           (rear == (front - 1 + size) % size);
  }
};
