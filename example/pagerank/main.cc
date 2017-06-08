#include <string>

#include "core/framework/edge.h"
#include "core/framework/graph.h"
#include "core/framework/graph_builder.h"
#include "core/framework/message.h"
#include "core/framework/reader.h"
#include "core/framework/vertex.h"
#include "core/platform/types.h"
#include "core/runtime/runner.h"

namespace example {
namespace pagerank {

class Message : public framework::MessageInterface {
public:
  platform::float32 msg;
};

class Edge : public framework::EdgeInterface {
public:
  bool read(char* buf, int size, int& offset) override {
    if (offset + 12 > size) {
      offset = size;
      return false;
    }
    src_idx = (buf[offset]<<24)|(buf[offset+1]<<16)
              |(buf[offset+2]<<8)|(buf[offset+3]);
    offset += 4;
    dst_idx = (buf[offset]<<24)|(buf[offset+1]<<16)
              |(buf[offset+2]<<8)|(buf[offset+3]);
    offset += 4;
    src_degree = (buf[offset]<<24)|(buf[offset+1]<<16)
              |(buf[offset+2]<<8)|(buf[offset+3]);
    offset += 4;
    return true;
  }

  void scatter(framework::GraphInterface* g,
      framework::MessageInterface* msg) override {
  }
private:
  platform::int64 src_idx, dst_idx, src_degree;
};

class Vertex : public framework::VertexInterface {
public:
  Vertex() {}

  void update(char* buf, platform::int64 offset) override {
  }

  void get(char* buf, platform::int64 offset,
      framework::MessageInterface* msg) override {
  }

  void gather(char*buf, platform::int64 offset,
      framework::MessageInterface* message) override {
  }
  void initOneVertex(char* buf, platform::int64 offset) {
  }
};

} // pagerank
} // example

int main() {
  std::string filePath= "/home/mlx/infomall_link_graph.bin.sorted";
  platform::int64 vNum = 3832209324L, eNum = 270497304397L;
  int iteration = 2;
  runtime::RunnerInterface* runner = new runtime::SimpleRunner<example::pagerank::Message, example::pagerank::Edge, example::pagerank::Vertex>(vNum, eNum, filePath);
  runner->run(iteration);
  return 0;
}
