#include <vk/long-poll.hpp>
#include <stdexcept>
#include <iostream>

using namespace vk;
using namespace nlohmann;
using namespace std;

LongPoll::LongPoll(const Bot *bot):
  bot_(bot)
{
  setServer();
}

LongPoll::~LongPoll()
{
  delete bot_;
}

void LongPoll::setServer()
{
  json response = bot_->call("groups.getLongPollServer",
  {
    {"group_id", to_string(bot_->getId())}
  });

  server_ = response["server"].get<string>();
  key_ = response["key"].get<string>();
  ts_ = to_string(response["ts"].get<int>());
}

json LongPoll::getUpdates()
{
  json j;

  while (true)
  {
    string data = bot_->getHttpClient()->makeRequest(server_ + "?act=a_check&key=" + key_ + "&ts=" + ts_ + "&wait=25");

    j = json::parse(data);
    ts_ = j["ts"].get<string>();

    cout << j << endl;

    if (j.find("failed") != j.end())
    {
      setServer();
    }
    else
    {
      break;
    }
  }

  return j["updates"];
}
