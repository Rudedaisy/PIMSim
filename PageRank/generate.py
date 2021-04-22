# Create a micro dataset that won't kill Gem5
import random
random.seed(1)

numNodes = 500

sources = []
dests = []

for source in range(numNodes):
    for dest in range(numNodes):
        if source != dest:
            if random.randint(0,99) > 50:
                sources.append(source)
                dests.append(dest)

fp = open("microdataset.txt", "w")

fp.write("# Directed graph (each unordered pair of nodes is saved once): microdataset.txt\n")
fp.write("# Description\n")
fp.write("# Nodes: " + str(numNodes) + " Edges: " + str(len(sources)) + "\n")
fp.write("# FromNodeId	ToNodeId\n")
for i in range(len(sources)):
    fp.write(str(sources[i]) + "\t" + str(dests[i]) + "\n")
fp.close()
