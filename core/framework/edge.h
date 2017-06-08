namespace framework {

class EdgeInterface {
public:
  EdgeInterface() = delete;
  virtual bool read(char* buf, int size, int& offset) = 0;
};

}
