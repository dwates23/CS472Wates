class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.graph = []

    def add_edge(self, u, v, w):
        self.graph.append([u, v, w])

    # Utility function to find the subset of an element i
    def find(self, parent, i):
        if parent[i] == i:
            return i
        return self.find(parent, parent[i])

    # Utility function to perform union of two subsets
    def union(self, parent, rank, x, y):
        xroot = self.find(parent, x)
        yroot = self.find(parent, y)

        if rank[xroot] < rank[yroot]:
            parent[xroot] = yroot
        elif rank[xroot] > rank[yroot]:
            parent[yroot] = xroot
        else:
            parent[yroot] = xroot
            rank[xroot] += 1

    # Function to implement Kruskal's algorithm
    def kruskal_mst(self):
        result = []
        i = 0
        e = 0

        self.graph = sorted(self.graph, key=lambda item: item[2])

        parent = []
        rank = []

        for node in range(self.V):
            parent.append(node)
            rank.append(0)

        while e < self.V - 1:
            u, v, w = self.graph[i]
            i += 1
            x = self.find(parent, u)
            y = self.find(parent, v)

            if x != y:
                e += 1
                result.append([u, v, w])
                self.union(parent, rank, x, y)

        return result

    # Function to implement Prim's algorithm
    def prim_mst(self):
        key = [float("inf")] * self.V
        parent = [None] * self.V
        mst_set = [False] * self.V

        # Start with the first vertex
        key[0] = 0
        parent[0] = -1

        for _ in range(self.V):
            u = self.min_key(key, mst_set)
            mst_set[u] = True

            # Update key values and parent for adjacent vertices
            for edge in self.graph:
                if edge[0] == u:
                    v = edge[1]
                    weight = edge[2]
                    if not mst_set[v] and weight < key[v]:
                        key[v] = weight
                        parent[v] = u

        # Create the MST
        mst = []
        for i in range(1, self.V):
            mst.append([parent[i], i, key[i]])

        return mst

    # Utility function to find the vertex with the minimum key value
    def min_key(self, key, mst_set):
        min_val = float("inf")
        min_index = -1

        for v in range(self.V):
            if key[v] < min_val and not mst_set[v]:
                min_val = key[v]
                min_index = v

        return min_index


# Testing the implementations
def test():
    # Create a graph with 4 vertices
    graph = Graph(4)
    graph.add_edge(0, 1, 10)
    graph.add_edge(0, 2, 6)
    graph.add_edge(0, 3, 5)
    graph.add_edge(1, 3, 15)
    graph.add_edge(2, 3, 4)

    # Test Kruskal's algorithm
    print("Kruskal's Minimum Spanning Tree:")
    kruskal_mst = graph.kruskal_mst()
    for u, v, w in kruskal_mst:
        print(f"{u} -- {v} == {w}")

    # Test Prim's algorithm
    print("\nPrim's Minimum Spanning Tree:")
    prim_mst = graph.prim_mst()
    for u, v, w in prim_mst:
        print(f"{u} -- {v} == {w}")


if __name__ == "__main__":
    test()
