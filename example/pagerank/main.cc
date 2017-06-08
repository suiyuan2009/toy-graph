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
  platform::db msg;
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
    framework::VertexInterface* src = nullptr;
    framework::VertexInterface* dst = nullptr;
    g->getVertex(src_idx, src);
    g->getVertex(dst_idx, dst);
    src->get(msg);
    Message* sendMsg = static_cast<Message*>(msg);
    sendMsg->msg = sendMsg->msg * 1.0 / src_degree;
    dst->gather(sendMsg);
  }
private:
  platform::ll src_idx, dst_idx, src_degree;
};

class Vertex : public framework::VertexInterface {
public:
  Vertex(platform::ll idx) : idx(idx) {
    value = 1.0;
    msg = 0.0;
  }

  void update() override {
    value = msg;
    msg = 0.0;
  }

  void get(framework::MessageInterface* msg) override {
    Message* m = static_cast<Message*>(msg);
    m->msg = value;
  }

  void gather(framework::MessageInterface* message) override {
    Message* m = static_cast<Message*>(message);
    msg += m->msg;
  }

private:
  platform::ll idx;
  platform::db value, msg;
};

} // pagerank
} // example

int main() {
  std::string filePath= "/home/mlx/infomall_link_graph.bin.sorted";
  platform::ll vNum = 3832209324L, eNum = 270497304397L;
  int iteration = 2;
  runtime::RunnerInterface* runner = new runtime::SimpleRunner<example::pagerank::Message, example::pagerank::Edge, example::pagerank::Vertex>(vNum, eNum, filePath);
  runner->run(iteration);
  return 0;
}
