from dimacs import *
from queue import PriorityQueue
import copy

name ='grid100x100'

(V, L) = loadWeightedGraph('graphs/'+name)

#(V, L) = loadWeightedGraph('graphs/in')

# for (x, y, c) in L:
#     print("krawedz miedzy", x, "i", y, "o wadze", c)


class Node:
    def __init__(self):
        self.edges = {}  # słownik par mapujący wierzchołki do których są krawędzie na ich wagi
        self.nr = []

    def addEdge(self, to, weight, ix=None):
        if weight!=0:
            self.edges[to] = self.edges.get(to, 0) + weight  # dodaj krawędź do zadanego wierzchołka
        if ix and ix not in self.nr:
            self.nr += [ix]  # o zadanej wadze; a jeśli taka krawędź
            # istnieje, to dodaj do niej wagę

    def delEdge(self, to):
        del self.edges[to]  # usuń krawędź do zadanego wierzchołka

    def __str__(self):
        res = str(self.nr) + ' :\t'
        for edge in self.edges:
            res += str(edge) + ' - ' + str(self.edges[edge]) + '\t'
        return res


G = [Node() for i in range(V + 1)]

for (x, y, c) in L:
    G[x].addEdge(y, c, x)
    G[y].addEdge(x, c, y)

# for node in G:
#     print(node)


def mergevertices(G, x, y):
    if x==y:
        return
    for edge in G[y].edges:
        if edge != x:
            G[x].addEdge(edge, G[y].edges[edge], y)
            G[edge].addEdge(x, G[edge].edges[y])
        else:
            G[x].addEdge(edge, 0, y)
        G[edge].delEdge(y)


# mergevertices(G, 3, 4)


# print('\n\n\n')
# for node in G:
#     print(node)


# def minimumcutphase(Graph):
#     G=Graph[:]
#     a = 1
#     #S = {}
#     S=set([])
#     #print(type(S))
#     Q = PriorityQueue()
#     Q.put((-0, a))
#     last = 0
#     prev = 0
#     D = [0 for i in range(V + 1)]
#
#     while len(S) < V:
#         ob = Q.get()[1]
#         if ob in S:
#             continue
#         #print(type({ob}), type(S))
#         #S = S + {ob}
#         S.add(ob)
#         for ver in G[ob].edges:
#             #print('?')
#             if ver not in S:
#                 D[ver] += G[ob].edges[ver]
#                 Q.put((-G[a].edges[ver], ver))
#         # pre=last
#         # prev,last=last,ob
#         prev = last
#         last = ob
#
#     wyn = 0
#     mergevertices(Graph, prev, last)
#     return wyn


def minimumcutphase(Graph, it):
    G=copy.deepcopy(Graph)#Graph[:]
    S = set([])

    a = 2
    Q = PriorityQueue()
    Q.put((-0, a))

    prev = a
    last = a
    while not Q.empty() and len(S)<V-it:
        tmp = Q.get()
        wyn, ob = tmp
        if ob in S:
            continue
        S.add(ob)

        prev = last
        last = ob
        if len(S)==V-it:
            break
        mergevertices(G, a, ob)

        for ver in G[ob].edges:
            if ver in S:
                continue
            Q.put((-G[a].edges[ver], ver))

    wyn = G[a].edges[last]
    mergevertices(Graph, last, prev)

    return wyn


sol=1e9

for i in range(V-1):
    print(i)
    sol = min(sol, minimumcutphase(G, i))
    # for nod in G:
    #     print('\t', nod)

print('\n', sol)


