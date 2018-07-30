#include <vk/bot.hpp>
#include <vk/long-poll.hpp>
#include <unistd.h>
#include <stdexcept>
#include <iostream>

using namespace vk;
using namespace nlohmann;
using namespace std;

Bot::Bot(const string &access_token):
  VK(),
  access_token_(access_token),
  id_(call("groups.getById")[0]["id"].get<id_t>())
{}

json Bot::call(const string &method, const map<string, string> &params) const
{
  map<string, string> my_params(params);

  my_params.insert(pair<string, string>("access_token", access_token_));
  my_params.insert(pair<string, string>("v", v_));

  json j;

  while (true)
  {
    string data = http_client_->makeRequest("https://api.vk.com/method/" + method + "?" + http_client_->buildQuery(my_params));

    j = json::parse(data);

    cout << j << endl;

    if (j.find("error") != j.end())
    {
      if (j["error"]["error_code"] == 6)
      {
        usleep(5000);
      }
      else
      {
        throw new std::runtime_error("Unhandled exception!");
      }
    }
    else
    {
      break;
    }
  }

  return j["response"];
}

id_t Bot::getId() const
{
  return id_;
}

void Bot::sendMessage(const id_t &user_id, const string &message, const string &keyboard) const
{
  map<string, string> params
  {
    {"user_id", to_string(user_id)},
    {"message", http_client_->encodeUrl(message)}
  };

  if (!keyboard.empty())
  {
    params.insert(pair<string, string>("keyboard", http_client_->encodeUrl(keyboard)));
  }

  call("messages.send", params);
}
