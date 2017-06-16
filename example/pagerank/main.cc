#include <iostream>
#include <string>

#include "core/framework/edge.h"
#include "core/framework/graph.h"
#include "core/framework/graph_builder.h"
#include "core/framework/message.h"
#include "core/framework/reader.h"
#include "core/framework/vertex.h"
#include "core/platform/types.h"
#include "core/runtime/runner.h"
#include "core/util/commandline.h"
#include "core/util/logging.h"

namespace example {
namespace pagerank {

// messge object used for data transmission.
class Message : public framework::MessageInterface {
public:
  // in pagerank example, only a float number need to be pass from src to dst
  // vertex.
  platform::float32 msg;
};

// edge object to read edge from input file and scatter infomation from src to
// dst.
class Edge : public framework::EdgeInterface {
public:
  // parse edge data from buf.
  void read(void* buf) override {
    platform::uint32* tmp_buf = (platform::uint32*)buf;
    src_idx = tmp_buf[0];
    dst_idx = tmp_buf[1];
    src_degree = tmp_buf[2];
  }
  // send src's pagerank info to dst.
  void scatter(framework::GraphInterface* g,
      framework::MessageInterface* msg) override {
    g->getVertexInfo(src_idx, msg);
    Message* tmp = (Message*)msg;
    tmp->msg = tmp->msg * 1.0 / src_degree;
    g->scatter(dst_idx, tmp);
  }
private:
  // edge variables.
  platform::int64 src_idx, dst_idx, src_degree;
};

// define vertex operations.
class Vertex : public framework::VertexInterface {
public:
  // how to update each vertex.
  void update(void* buf) override {
    platform::float32* tmp_buf = (platform::float32*)buf;
    tmp_buf[0] = tmp_buf[1] * 0.85 + 0.15;
    tmp_buf[1] = 0;
  }
  // get the value of the vertex as a message.
  void getValue(void* buf, framework::MessageInterface* msg) override {
    platform::float32* tmp_buf = (platform::float32*)buf;
    Message* tmp = (Message*)msg;
    tmp->msg = tmp_buf[0];
  }
  // how to gather message from src.
  void gather(void* buf, framework::MessageInterface* msg) override {
    platform::float32* tmp_buf = (platform::float32*)buf;
    Message* tmp = (Message*)msg;
    tmp_buf[1] += tmp->msg;
  }
  // init the vertex.
  void init(void* buf) override {
    platform::float32* tmp_buf = (platform::float32*)buf;
    tmp_buf[0] = 1.0;
    tmp_buf[1] = 0.0;
  }
  // return the infomation needed to write to result file.
  std::string getOutput(void* buf, platform::int64 idx) override {
    platform::float32* tmp_buf = (platform::float32*)buf;
    return std::to_string(idx) + "\t" + std::to_string(tmp_buf[0]) + "\n";
  }
};

} // pagerank
} // example

int main(int argc, char* argv[]) {
  LOG(util::INFO) << "this is an example of how to use toy-graph.";
  // a commandline parser.
  util::CommandLine cmdl = util::CommandLine();
  cmdl.addOption("input").addOption("output").addOption("vertexNum")
      .addOption("edgeNum").addOption("iterations");
  cmdl.parseCommandLine(argc, argv);
  std::string inputPath = cmdl.getOptVal("input");
  std::string outputPath = cmdl.getOptVal("output");
  platform::int64 vNum = std::stoll(cmdl.getOptVal("vertexNum"));
  platform::int64 eNum = std::stoll(cmdl.getOptVal("edgeNum"));
  int iteration = std::stoi(cmdl.getOptVal("iterations"));
  int oneVertexSize = 8, oneEdgeSize = 12;
  // a runner to run computation.
  std::unique_ptr<runtime::RunnerInterface> runner(new runtime::SimpleRunner<
      example::pagerank::Message, example::pagerank::Edge,
          example::pagerank::Vertex>(vNum, eNum, inputPath, outputPath,
              oneVertexSize, oneEdgeSize));
  runner->run(iteration);
  return 0;
}
