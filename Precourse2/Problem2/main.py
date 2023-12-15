from sys import stdin, argv

def width_of_binary_tree(args):
    '''
    Calculate the widest level and the width of that level
    =================================================================================================
    Arguments:
        + args: something containing information about the input binary tree
    Outputs:
        + widest_level: widest level of given binary tree
        + max_width: widht of the widest level of given binary tree
    '''

    class Grid_tree:

        def __init__(self, args):
            self.graph = args["graph"]
            self.num = args["number_of_nodes"]
            self.node_levels = [0 for _ in range(self.num)]
            self.node_column = [0 for _ in range(self.num)]
            self.column_count = 0
            self.level_width = [0 for _ in range(self.num)]

        def get_root(self):
            self.has_parent = [False for _ in range(self.num)]
            for child_1, child_2 in self.graph.values():
                self.has_parent[child_1] = True
                self.has_parent[child_2] = True
            for i, value in enumerate(self.has_parent):
                if not value:
                    return i


        def dfs(self, current_node, level):
            self.node_levels[current_node] = level
            child_1, child_2 = self.graph[current_node]
            if child_1 > -2:
                self.dfs(child_1, level + 1)
            self.column_count += 1
            self.node_column[current_node] = self.column_count
            if child_2 > -2:
                self.dfs(child_2, level + 1)

            if (child_1 > -2 and child_2 > -2):
                current_width = self.node_column[child_2] - self.node_column[child_1] + 1
                self.level_width[level + 1] = max(self.level_width[level + 1], current_width)

    
    grid_tree = Grid_tree(args)
    grid_tree.dfs(grid_tree.get_root(), 0)

    widest_level = 0
    for level in range(grid_tree.num):
        if grid_tree.level_width[level] > grid_tree.level_width[widest_level]:
            widest_level = level

    return widest_level + 1, grid_tree.level_width[widest_level]

def main():

    input_file = argv[1]

    args = {"total_nodes" : 0, "graph" : {}}
    with open(input_file, 'r') as file:
        lines = file.readlines()
        args["number_of_nodes"] = int(lines[0])
        for line in lines[1:]:
            line = line.strip().split()
            # minus 1 for all input numbers
            parent, child_1, child_2 = int(line[0]) - 1, int(line[1]) - 1, int(line[2]) - 1
            if parent not in args["graph"]:
                args["graph"][parent] = (child_1, child_2)

    output = width_of_binary_tree(args)

    with open("output.txt", "w") as f:
        f.write(f"{output[0]} {output[1]}\n")

if __name__ == "__main__":
    main()
