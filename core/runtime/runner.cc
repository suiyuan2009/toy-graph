#include "core/framework/reader.h"
#include "core/runtime/runner.h"

namespace runtime {

RunnerInterface::~RunnerInterface() {
  delete(graph);
  delete(reader);
}

template <class MessageT, class EdgeT, class VertexT>
SimpleRunner<MessageT, EdgeT, VertexT>::SimpleRunner(platform::ll vertexNum,
    platform::ll edgeNum, std::string filePath) {
  file = filePath;
  framework::GraphBuilderInterface* gbuild = new
      framework::SimpleGraphBuilder<VertexT>();
  graph = gbuild->build(vertexNum, edgeNum);
  delete(gbuild);
};

template <class MessageT, class EdgeT, class VertexT>
void SimpleRunner<MessageT, EdgeT, VertexT>::run(int iteration) {
  for (int i = 1; i <= iteration; i++) {
    delete(reader);
    reader = new framework::SimpleReader(file);
    framework::EdgeInterface* tmp = new EdgeT();
    framework::MessageInterface* msg = new MessageT();
    while (reader->get(tmp)) {
      tmp->scatter(graph, msg);
    }
    graph->update();
  }
};

}
