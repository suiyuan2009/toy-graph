#ifndef CORE_RUNTIME_RUNNER_H
#define CORE_RUNTIME_RUNNER_H

#include <iostream>
#include <memory>
#include <string>

#include "core/framework/graph.h"
#include "core/framework/graph_builder.h"
#include "core/framework/reader.h"
#include "core/framework/writer.h"
#include "core/platform/types.h"
#include "core/util/logging.h"

namespace runtime {

class RunnerInterface {
public:
  virtual void run(int iteration) = 0;
  virtual ~RunnerInterface();
protected:
  framework::GraphInterface* graph;
  framework::ReaderInterface* reader;
  framework::WriterInterface* writer;
};


template <class MessageT, class EdgeT, class VertexT>
class SimpleRunner : public RunnerInterface {
public:
  void run(int iteration);
  SimpleRunner(platform::int64 vertexNum, platform::int64 edgeNum,
      std::string inputPath, std::string outputPath);
private:
  std::string inputFile;
  std::string outputFile;
};

RunnerInterface::~RunnerInterface() {
  delete(graph);
  delete(reader);
  delete(writer);
}

template <class MessageT, class EdgeT, class VertexT>
SimpleRunner<MessageT, EdgeT, VertexT>::SimpleRunner(platform::int64 vertexNum,
    platform::int64 edgeNum, std::string inputPath, std::string outputPath) {
  inputFile = inputPath;
  outputFile = outputPath;
  std::unique_ptr<framework::GraphBuilderInterface> gbuild(new
      framework::SimpleGraphBuilder<VertexT>());
  LOG(util::DEBUG)<<"start build graph, vertex num is "<<vertexNum<<
      ", edge num is "<<edgeNum<<std::endl;
  graph = gbuild->build(vertexNum, edgeNum);
  writer = new framework::SimpleWriter(outputFile);
};

template <class MessageT, class EdgeT, class VertexT>
void SimpleRunner<MessageT, EdgeT, VertexT>::run(int iteration) {
  for (int i = 1; i <= iteration; i++) {
    delete(reader);
    LOG(util::DEBUG)<<"start iteration: "<<i<<std::endl;
    reader = new framework::SimpleReader(inputFile);
    framework::EdgeInterface* edge = new EdgeT();
    framework::MessageInterface* msg = new MessageT();
    platform::int64 edgeNumDEBUG = 0;
    int processPercent = 0;
    platform::int64 percent = graph->getEdgeNum() / 100;
    LOG(util::DEBUG)<<"edge percent is "<<percent<<std::endl;
    while (reader->get(edge)) {
      edge->scatter(graph, msg);
      edgeNumDEBUG++;
      if (edgeNumDEBUG == percent) {
        processPercent++;
        edgeNumDEBUG = 0;
        LOG(util::DEBUG)<<"process %"<<processPercent<<" edges"<< std::endl;
      }
    }
    LOG(util::DEBUG)<<"process %100 edges"<< std::endl;
    delete(edge);
    delete(msg);
    graph->updateAllVertex();
    LOG(util::DEBUG)<<"finish iteration: "<<i<<std::endl;
  }
  for (platform::int64 i = 0; i < graph->getVertexNum(); i++) {
    writer->write(graph->getVertexOutput(i));
  }
};

}
#endif
