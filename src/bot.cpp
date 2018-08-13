#include <vk/bot.hpp>
#include <vk/long-poll.hpp>

using namespace vk;
using namespace std;

Bot::Bot(const string &access_token):
  VK(access_token),
  id_(call("groups.getById")[0]["id"].get<id_t>())
{}

id_t Bot::getId() const
{
  return id_;
}

void Bot::sendMessage(const id_t &user_id, const string &message, const string &keyboard) const
{
  map<string, string> params
  {
    {"user_id", to_string(user_id)},
    {"message", message}
  };

  if (!keyboard.empty())
  {
    params.insert(pair<string, string>("keyboard", keyboard));
  }

  call("messages.send", params);
}
