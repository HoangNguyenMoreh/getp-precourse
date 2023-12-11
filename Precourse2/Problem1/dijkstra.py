import heap

def dijkstra(graph, start):
    distances = {node: float('inf') for node in graph}

    distances[start] = 0
    min_heap = heap.MinHeap()
    min_heap.heap = [(0, start)]
    while len(min_heap.heap) > 0:
        min_in_heap = min_heap.pop()
        current_node = min_in_heap[1]
        for adjacent_node in graph[current_node]:
            distance_to_compare = distances[current_node] + graph[current_node][adjacent_node]
            if distances[adjacent_node] > distance_to_compare:
                distances[adjacent_node] = distance_to_compare
                min_heap.push((distance_to_compare, adjacent_node))

    return distances

if __name__ == "__main__":
    graph = {}
    with open('input_graph.txt', 'r') as file:
        lines = file.readlines()
        for line in lines:
            line = line.strip().split()
            node1, node2, weight = line[0], line[1], int(line[2])
            if node1 not in graph:
                graph[node1] = {}
            graph[node1][node2] = weight

    start_node = 'A'
    result = dijkstra(graph, start_node)
    print(f"Start Node: {start_node}")
    print(f"Shortest distances: {result}")
