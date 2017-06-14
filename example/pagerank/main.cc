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
#include "core/util/logging.h"

namespace example {
namespace pagerank {

class Message : public framework::MessageInterface {
public:
  platform::float32 msg;
};

class Edge : public framework::EdgeInterface {
public:
  bool read(void* buf, int size, int& offset) override {
    if (offset + 12 > size) {
      offset = size;
      return false;
    }
    platform::uint32* tmp_buf = (platform::uint32*)buf;
    src_idx = tmp_buf[offset>>2];
    dst_idx = tmp_buf[(offset>>2) + 1];
    src_degree = tmp_buf[(offset>>2) + 2];
    offset += 12;
    //std::cout<<src_idx<<" "<<dst_idx<<" "<<src_degree<<std::endl;
    return true;
  }

  void scatter(framework::GraphInterface* g,
      framework::MessageInterface* msg) override {
    g->getVertexInfo(src_idx, msg);
    Message* tmp = (Message*)msg;
    //LOG(util::DEBUG) << "edge scatter function, message value is "
    //                 << tmp->msg << "src degree is "
    //                 << src_degree << std::endl;
    tmp->msg = tmp->msg * 1.0 / src_degree;
    g->scatter(dst_idx, tmp);
  }
private:
  platform::int64 src_idx, dst_idx, src_degree;
};

class Vertex : public framework::VertexInterface {
public:
  Vertex() {}

  void update(void* buf, platform::int64 offset) override {
    platform::float32* tmp_buf = (platform::float32*)buf;
    tmp_buf[offset>>2] = tmp_buf[(offset>>2)+ 1] * 0.85 + 0.15;
  }

  void get(void* buf, platform::int64 offset,
      framework::MessageInterface* msg) override {
    platform::float32* tmp_buf = (platform::float32*)buf;
    Message* tmp = (Message*)msg;
    tmp->msg = tmp_buf[offset>>2];
  }

  void gather(void*buf, platform::int64 offset,
      framework::MessageInterface* msg) override {
    platform::float32* tmp_buf = (platform::float32*)buf;
    Message* tmp = (Message*)msg;
    //LOG(util::DEBUG) << "vertex gather function, message value is "
    //                 << tmp->msg << std::endl;
    tmp_buf[(offset>>2) + 1] += tmp->msg;
  }
  void initOneVertex(void* buf, platform::int64 offset) override {
    platform::float32* tmp_buf = (platform::float32*)buf;
    tmp_buf[offset>>2] = 1.0;
    tmp_buf[(offset>>2) + 1] = 0.0;
  }

  std::string getOutput(void* buf, platform::int64 offset,
      platform::int64 idx) override {
    platform::float32* tmp_buf = (platform::float32*)buf;
    return std::to_string(idx) + "\t" + std::to_string(tmp_buf[offset>>2]) +
           "\n";
  }
};

} // pagerank
} // example

int main() {
  std::string filePath= "/home/suiyuan2009/infomall_link_graph.bin";
  std::string outputPath= "/home/suiyuan2009/infomall_pagerank_value";
  platform::int64 vNum = 3832209324L, eNum = 70497304397L;
  int iteration = 1;
  runtime::RunnerInterface* runner = new runtime::SimpleRunner<
      example::pagerank::Message, example::pagerank::Edge,
          example::pagerank::Vertex>(vNum, eNum, filePath, outputPath);
  runner->run(iteration);
  delete(runner);
  return 0;
}
