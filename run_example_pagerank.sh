bazel build //example/pagerank:main
#./bazel-bin/example/pagerank/main --input /home/suiyuan2009/infomall_link_graph.bin --output /home/suiyuan2009/infomall_pagerank_value --vertexNum 3832209324 --edgeNum 70497304397 --iterations 5
valgrind --leak-check=full --show-leak-kinds=all ./bazel-bin/example/pagerank/main --input /home/webg/p2p-Gnutella08.pr_input.bin --output /home/suiyuan2009/p2p_pagerank_value --vertexNum 6301 --edgeNum 20777 --iterations 5
