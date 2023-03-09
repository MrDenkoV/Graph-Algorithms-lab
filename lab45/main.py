from dimacs import *

name = 'maxclique/simple'#interval-rnd8'

#name = 'tst.in'

class Node:
    def __init__(self, idx):
        self.idx = idx
        self.out = set()              # zbiór sąsiadów

    def connect_to(self, v):
        self.out.add(v)


def checkLexBFS(G, vs):
    n = len(G)
    pi = [None] * n
    for i, v in enumerate(vs):
        pi[v] = i

    for i in range(n-1):
        for j in range(i+1, n-1):
            Ni = G[vs[i]].out
            Nj = G[vs[j]].out

            verts = [pi[v] for v in Nj - Ni if pi[v] < i]
            if verts:
                viable = [pi[v] for v in Ni - Nj]
                if not viable or min(verts) <= min(viable):
                    return False
    return True


(V, L) = loadWeightedGraph(name)

G = [None] + [Node(i) for i in range(1, V+1)]  # żeby móc indeksować numerem wierzchołka

for (u, v, _) in L:
    G[u].connect_to(v)
    G[v].connect_to(u)

for i in G:
    if i is not None:
       print(i.idx, end=': ')
       for j in i.out:
           print(j, end=', ')
    print('')

#print(type(S), type(S[-1]))


def lexBFS(G):
    S = [{i for i in range(2, V+1)}]
    S += [{1}]
    # print(S)
    vis = []
    while len(vis) < V:
        print(S)
        ob = []
        el = S[-1].pop()
        vis += [el]
        for zb in S:
            tmpp = zb - G[el].out
            tmpn = zb & G[el].out

            if tmpp:
                ob += [tmpp]
            if tmpn:
                ob += [tmpn]

        S = ob
    return vis


order = lexBFS(G)
print(order)

print(checkLexBFS(G, order))


def PEO(G, order, RN, P):
    par(RN, order, G)
    for i in range(V, 0, -1):
        j=i-1
        while j>0 and not RN[order[i-1]] & {order[j-1]}:
            j-=1
            #print('in ', j)
        # print(G[order[i-1]].out)
        # print(order[j-1])
        #print('out ', j)
        if j==0:
            continue
        P[order[i-1]]=order[j-1]
        print(order[i-1], RN[order[i-1]], order[j-1], RN[order[i-1]] & {order[j-1]})
    print('P: ', P)

    for i in range(1, V+1):
        if P[i]!=0 and not (RN[i]-{P[i]}) <= RN[P[i]]:
            #print((RN[i]-{P[i]}), RN[P[i]], (RN[i]-{P[i]}) <= RN[P[i]], P[i])
            return False
    return True


def par(RN, order, G):
    vis = set()
    for i in order:
        RN[i] = vis & G[i].out
        vis |= {i}


parent=[0 for i in range(V+1)]
RN=[set() for i in range(V+1)]

#par(RN, order, G)
print(PEO(G, order, RN, parent))

print(RN)


class TreeNode:
    def __init__(self):
        self.kids=[]

    def addKid(self, node):
        self.kids.append(node)


class CliqueNode:
    def __init__(self, clique):
        self.clique=clique
        self.n=[]


def preOrder(T, C, RN, parent, cliques, v):
    if RN[v] == C[parent[v]]:
        C[parent[v]].clique |= {v}
        C[v] = C[parent[v]]
    else:
        C[v] = CliqueNode(RN[v] | {v})
        C[v].n.append(C[parent[v]])
        C[parent[v]].append(C[v])
        cliques.append(C[v])
    print(v," ",T[v].kids," ",parent[v]," ",RN[v])
    for i in T[v].kids:
        preOrder(T, C, RN, parent, cliques, i)


def makeTree(G, order, RN, parent):
    T=[TreeNode() for i in range(len(order)+1)]

    for v in order:
        if parent[v]!=0:
            T[parent[v]].addKid(v)

    C=[None for i in range(len(order)+1)]

    s=order[0]
    C[s]=CliqueNode({s})
    cliques=[C[s]]

    for i in T[s].kids:
        preOrder(T, C, RN, parent, cliques, v)


makeTree(G, order, RN, parent)
