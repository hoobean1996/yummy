#pragma once

namespace cetty {

class Listener {
public:
  Listener();
  ~Listener();

  bool getStatus();

  int accept();
};

Listener listen(int port);
} // namespace cetty