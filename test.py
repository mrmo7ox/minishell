from graphviz import Digraph

class TreeNode:
    def __init__(self, value):
        self.value = value
        self.children = []

def parse_input(input_str):
    lines = input_str.strip().splitlines()
    nodes = []
    for line in lines:
        stripped = line.lstrip()
        indent = len(line) - len(stripped)
        level = indent // 3  # assuming 3 spaces indent
        nodes.append((level, stripped))

    root = TreeNode(nodes[0][1])
    stack = [(0, root)]

    for level, value in nodes[1:]:
        node = TreeNode(value)
        while stack and stack[-1][0] >= level:
            stack.pop()
        parent = stack[-1][1]
        parent.children.append(node)
        stack.append((level, node))

    return root

def add_nodes_edges(dot, node, parent_id=None, counter=[0]):
    # Create unique ID for the node
    node_id = str(counter[0])
    counter[0] += 1

    # Add node to graph
    dot.node(node_id, node.value)

    # Add edge from parent to current node
    if parent_id is not None:
        dot.edge(parent_id, node_id)

    # Recursively add children
    for child in node.children:
        add_nodes_edges(dot, child, node_id, counter)

def main():
    input_data = """
|| (root)
   0 (left)
   && (right)
      || (left)
         || (right)
            && (left)
               2 (left)
            4 (right)
      | (right)
         4 (left)
         5 (right)
    """

    root = parse_input(input_data)
    dot = Digraph(comment='Shell Command Tree')
    add_nodes_edges(dot, root)

    # Save the dot source file only
    dot.save('shell_command_tree.dot')
    print("DOT source saved to shell_command_tree.dot")

if __name__ == "__main__":
    main()
