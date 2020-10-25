#pragma once
#include "MessagingChannel.h"
#include "BackgroundThread.h"

namespace Lux::Networking
{
  class messaging_client
  {
  public:
    messaging_client();

    Events::event_publisher<messaging_client*, messaging_channel*> connected;

    message_task send(Serialization::memory_stream&& message);

    bool is_connected() const;
    Events::event_publisher<messaging_client*, bool> is_connected_changed;

    virtual ~messaging_client();

  protected:
    virtual std::unique_ptr<messaging_channel> get_client() = 0;

  private:
    Events::event_owner _events;
    std::mutex _mutex;
    std::unique_ptr<messaging_channel> _channel;
    Threading::background_thread _connection_thread;
    Threading::manual_reset_event _is_disposed;

    void connect();
  };
}