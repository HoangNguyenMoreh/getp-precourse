class MinHeap:

    def __init__(self):
        self.heap = []


    def get_parent_index(self, child_id):
        return ((child_id + 1) >> 1) - 1


    def get_children_indices(self, parent_id):
        child_index_1 = (parent_id << 1) + 1
        child_index_2 = (parent_id << 1) + 2
        return [child_index_1, child_index_2]


    def push(self, value):
        self.heap.append(value)
        current_id = len(self.heap) - 1
        parent_id = self.get_parent_index(current_id)

        while parent_id >= 0:
            if self.heap[parent_id] > self.heap[current_id]:
                self.heap[parent_id], self.heap[current_id] = self.heap[current_id], self.heap[parent_id]
                current_id = parent_id
                parent_id = self.get_parent_index(current_id)
            else:
                break
        

    def pop(self):
        if len(self.heap) == 0:
            return 0
        if len(self.heap) == 1:
            return self.heap.pop()
        return_value = self.heap[0]
        self.heap[0] = self.heap.pop()
        current_id = 0
        child_index_1, child_index_2 = self.get_children_indices(current_id)

        while (child_index_1 < len(self.heap)) and (child_index_2 < len(self.heap)):
            if self.heap[current_id] > min(self.heap[child_index_1], self.heap[child_index_2]):
                child_to_swap = child_index_1
                if self.heap[child_index_1] > self.heap[child_index_2]:
                    child_to_swap = child_index_2
                self.heap[child_to_swap], self.heap[current_id] = self.heap[current_id], self.heap[child_to_swap]
                current_id = child_to_swap
                child_index_1, child_index_2 = self.get_children_indices(current_id)
            else:
                break

        if (child_index_1 < len(self.heap)) and (self.heap[current_id] > self.heap[child_index_1]):
            self.heap[child_index_1], self.heap[current_id] = self.heap[current_id], self.heap[child_index_1]

        return return_value
        

    def heapify(self):
        min_heap = MinHeap()
        for item in self.heap:
            min_heap.push(item)
        self.heap = min_heap.heap

if __name__ == "__main__":
    min_heap = MinHeap()

    with open('input_heap.txt', 'r') as file:
        lines = file.readlines()
        for line in lines:
            value = int(line.strip())
            min_heap.push(value)

    print("Min heap : ", min_heap.heap)
