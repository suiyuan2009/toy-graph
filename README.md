# introduction

`toy-graph` is a purely c++ CPU based multithreading graph computing system
aiming to support billions vertexes.

# quick start

use pagerank as an example, for api usage, see [pagerank example](https://github.com/suiyuan2009/toy-graph/blob/master/example/pagerank/main.cc).

1. install bazel.

`toy-graph` is built using [bazel](https://bazel.build/versions/master/docs/install.html),
follow the installation guide to install it.

2. compile pagerank program.

```
bazel build //example/pagerank:main
```

3. prepare graph input file

raw input file is `test/pagerank_test_graph`, each line is an edge, format is
`src dst src_degree`(pagerank task specific). we need to convert this file to
binary first, we use 4 bytes to represent each variable(12 bytes each edge). run
```
bazel build //tool:convert_to_binary
```
to compile convert tool. In `test`
directory, run
```
../bazel-bin/tool/convert_to_binary --input pagerank_test_graph
--output pagerank_test_graph.bin
```
then we get `.bin` binary graph input file.

4. run pagerank example

in `toy-graph` project directory, run
```
./bazel-bin/example/pagerank/main --input
test/pagerank_test_graph.bin --output test/pagerank_test_graph.pagerank
--vertexNum 5 --edgeNum 5 --iterations 1
```
finally we get
`test/pagerank_test_graph.pagerank` result file, each line is
`vertex_index pagerank_value` format.

# system requirements(only linux tested)

Currently `toy-graph` supports single machine vertex in memory & pull
computation, one thread to read, multi threads to compute, memory cost is
each_vertex_cost * num_of_vertex. There is no disk space needed except result
file.

# performance

1. we use [valgrind](http://valgrind.org/docs/manual/quick-start.html) to do
memory check, such as memory leak, we use [gtest](https://github.com/google/googletest)
to do unit test).

2. In order to reduce memory cost, all vertexes are stored on a continuous memory
buffer instead of a vector of objects(aligned memory can increase memory cost).
We leave each vertex memory management to user themselves.

3. to be continued(such as comparative experiments).

# road map

1. speed optimization, unit tests and experiment results.
2. support push computation model.
3. add code comments, add docs.
4. support multi platforms.
5. support distributed computation.
