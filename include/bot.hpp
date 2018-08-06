#ifndef BOT_HPP_INCLUDED
#define BOT_HPP_INCLUDED

#include "base-types.hpp"
#include "vk.hpp"

namespace vk
{
  class Bot:
    public VK
  {
  public:
    Bot(const std::string &access_token);
    id_t getId() const;
    void sendMessage(const id_t &user_id, const std::string &message, const std::string &keyboard = "") const;

  private:
    const id_t id_;
  };
}

#endif
