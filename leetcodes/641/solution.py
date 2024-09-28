class Node:
    def __init__(self, val, next_node, prev_node):
        self.val = val
        self.next = next_node
        self.prev = prev_node

class MyCircularDeque(object):

    def __init__(self, k):
        """
        :type k: int
        """
        self.sizes = k
        self.curr_sizes = 0
        self.head = Node(None, None, None)
        self.last = Node(None, self.head, self.head)
        self.head.prev = self.last
        self.head.next = self.last

    def _insert(self, node1, node2):
        node1.next, node2.next, node2.prev, node1.next.next.prev = node2, node1.next, node1, node2

    def _delete(self, node):
        node.prev.next, node.next.prev = node.next, node.prev

    def insertFront(self, value):
        """
        :type value: int
        :rtype: bool
        """
        if (self.curr_sizes == self.sizes):
            return False
        self.curr_sizes += 1
        self._insert(self.head, Node(value,None,None))
        return True
        

    def insertLast(self, value):
        """
        :type value: int
        :rtype: bool
        """
        if (self.curr_sizes == self.sizes):
            return False
        self.curr_sizes += 1
        self._insert(self.last.prev, Node(value,None,None))
        return True
       

    def deleteFront(self):
        """
        :rtype: bool
        """
        if (self.head.next == self.last):
            return False
        self.curr_sizes -= 1
        self._delete(self.head.next)
        return True
        

    def deleteLast(self):
        """
        :rtype: bool
        """
        if (self.last.prev == self.head):
            return False
        self.curr_sizes -= 1
        self._delete(self.last.prev)
        return True
        

    def getFront(self):
        """
        :rtype: int
        """
        return self.head.next.val if self.head.next.val != None else -1
        

    def getRear(self):
        """
        :rtype: int
        """
        return self.last.prev.val if self.last.prev.val != None else -1

    def isEmpty(self):
        """
        :rtype: bool
        """
        return self.head.next == self.last
        

    def isFull(self):
        """
        :rtype: bool
        """
        return self.curr_sizes >= self.sizes
