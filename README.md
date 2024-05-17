Managing a ranking between graphs weighted direct graphs
- The ranking keeps track of the k 'best' graphs
- The programme to be implemented receives as input
- two parameters, once only (on the first line of the file, separated by space)
- d: the number of nodes in the graphs
- k: the length of the ranking
- A sequence of commands between
- AddGraph [matrix-adjacent].
- TopK
d, k and the number of graphs can be represented by 32-bit integers.
It requires adding a graph to those considered for ranking.
Followed by the adjacency matrix of the graph itself, printed one line per each row, with the elements separated by commas.
The nodes of the graph are to be considered logically labelled with an index integer between 0 and d-1;
the node in position 0 is the one whose outgoing star is described by the first row of the matrix.
