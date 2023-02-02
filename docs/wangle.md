# wangle
- asynchrnous
- event-driven

```c++

class EchoHandler: public HandlerAdapter<std::string> {
  public:
    virtual void read(Context *context, std::string message) override {
      // process

      write(context, message + "\r\n");
    }
}


class EchoPipelineFactory: public PipelineFactory<EchoPipeline> {
  public:
    EchoPipeline::Ptr newPipeline(std::shared_ptr<AsyncTransport> sock) {
      auto pipeline = EchoPipeline::create();
      pipeline->addBack(AsyncSocketHandler(sock));
      pipeline->addBack(LineBasedFrameDecoder(8192));
      pipeline->addBack(StringCodec());
      pipeline->finalize();
      return pipeline;
    }
}

```