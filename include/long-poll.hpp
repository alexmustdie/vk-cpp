#ifndef LONGPOLL_HPP_INCLUDED
#define LONGPOLL_HPP_INCLUDED

#include "bot.hpp"

namespace vk
{
  class LongPoll
  {
  public:
    LongPoll(const Bot *bot);
    ~LongPoll();
    void setServer();
    nlohmann::json getUpdates();

  private:
    std::string server_;
    std::string key_;
    std::string ts_;
    const Bot *bot_;
  };
}

#endif
