from dimacs import *
from sys import argv
import copy

file = 'simple'#'rand100_500'#argv[1]

path = "connectivity/"+file#"flow/"+file

(V, L) = loadWeightedGraph(path)

# to, cap, flow, op
G = [[] for i in range(V+1)]
#to, -flow, op
P = [[] for i in range(V+1)]

for i in L:
    G[i[0]].append([i[1], i[2], 0, len(P[i[1]])])
    P[i[1]].append([i[0], 0, len(G[i[0]])-1])


def DFS(G, P, pop, ob=1, t=V):
    if ob == t:
        return 1e9
    for i in G[ob]:
        if i[1]-i[2] > 0 and pop[i[0]] == -1:
            pop[i[0]] = ob
            tmp = DFS(G, P, pop, i[0], t)
            if tmp != 0:
                return min(i[1]-i[2], tmp)

    for i in P[ob]:
        if i[1] < 0 and pop[i[0]] == -1:
            pop[i[0]] = ob
            tmp = DFS(G, P, pop, i[0], t)
            if tmp != 0:
                return min(-i[1], tmp)

    return 0


Graph=G
Par=P

wyn=1e9

for i in range(1, V+1):
    sum = 0
    G=copy.deepcopy(Graph)
    P=copy.deepcopy(Par)
    for j in range(i+1, V+1):
        while(True):
            pop = [-1 for i in range(V+1)]
            dfs = DFS(G, P, pop, i, j)
            if dfs == 0:
                break
            x = V
            sum += dfs
            while x != 1:
                par = pop[x]
                fs=False
                for i in G[par]:
                    if i[0] == x:
                        i[2] += dfs
                        P[x][i[3]][1]-=dfs
                        fs=True
                        break

                if not fs:
                    for i in P[par]:
                        if i[0] == x:
                            i[1]+=dfs
                            G[x][i[2]][2]-=dfs
                            break

                x = par
        wyn = min(wyn, sum)
print(wyn)
