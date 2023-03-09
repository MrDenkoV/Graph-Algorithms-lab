import networkx as nx
from dimacs import *
from sys import argv


def checkPlanar(name="simple"):
    name="plnar/"+name
    G = nx.Graph()
    (V, L) = loadWeightedGraph(name)
    G.add_nodes_from([i for i in range(1, V+1)])
    G.add_edges_from((edge[0], edge[1]) for edge in L)
    for v in G.nodes:
        print(v, end=" :")
        for e in G[v]:
            print(e, end=' ')
        print('')
    return nx.check_planarity(G)[0]


def flow(name="simple"):
    name="flow/"+name
    G = nx.DiGraph()
    (V, L) = loadDirectedWeightedGraph(name)
    G.add_nodes_from([i for i in range(1, V+1)])
    G.add_edges_from([(edge[0], edge[1]) for edge in L])
    for edge in L:
        G[edge[0]][edge[1]]['capacity']=edge[2]
        print(edge[2])
    for v in G.nodes:
        print(v, end=" :")
        for e in G[v]:
            print(e, '-', G[v][e], end='   ')
        print('')
    return nx.maximum_flow(G, 1, V)[0]


def sat2(name="simple_sat"):
    name="sat/"+name
    G = nx.DiGraph()
    (V, L) = loadCNFFormula(name)
    G.add_nodes_from([i for i in range(-V, V+1)])
    G.remove_node(0)
    for edge in L:
        G.add_edge(-edge[0], edge[1])
        G.add_edge(-edge[1], edge[0])
    SCC = list(nx.strongly_connected_components(G))
    t=0
    for S in SCC:
        print("Silnie spojna składowa", t, "zawiera wierzcholki")
        for v in S:
            print("  ", v)
        t += 1
    print(SCC)
    T=nx.DiGraph()
    SSS=dict()
    t=0
    for S in SCC:
        z=set()
        # print(S)
        T.add_node(t)
        for v in S:
            if {-v} & z:
                return False
            z |= {v}
            # print(z, v)
            SSS[v]=t
        t+=1
    #for v in G.nodes:
        #if T[


    return True


# print(checkPlanar(argv[1]))

# print(flow(argv[2]))

print(sat2(argv[1]))
