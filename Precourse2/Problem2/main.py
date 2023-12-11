from sys import stdin

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
    graph = args["graph"]
    num = args["number_of_nodes"]
    node_levels = [0 for i in range(num)]
    node_column = [0 for i in range(num)]
    column_count = 0
    level_width = [0 for i in range(num)]

    def dfs(current_node, level):
        nonlocal column_count

        node_levels[current_node] = level
        (child_1, child_2) = graph[current_node]
        if child_1 != -2:
            dfs(child_1, level + 1)
        column_count += 1
        node_column[current_node] = column_count
        if child_2 != -2:
            dfs(child_2, level + 1)

        if (child_1 != -1 and child_2 != -1):
            current_width = node_column[child_2] - node_column[child_1] + 1
            level_width[level + 1] = max(level_width[level + 1], current_width)

    # assuming root of the tree is node 1
    dfs(0, 0)

    widest_level = 0
    for level in range(num):
        if level_width[level] > level_width[widest_level]:
            widest_level = level

    return widest_level + 1, level_width[widest_level]

def main():

    args = {"total_nodes" : 0, "graph" : {}}
    with open('input.txt', 'r') as file:
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
