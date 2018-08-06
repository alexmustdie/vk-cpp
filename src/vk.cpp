#include <vk/vk.hpp>
#include <chrono>
#include <thread>
#include <stdexcept>
#include <iostream>

using namespace vk;
using namespace http_client;
using namespace nlohmann;
using namespace std;

VK::VK(const string &access_token, const string &v):
  http_client_(new HttpClient),
  access_token_(access_token),
  v_(v)
{}

VK::~VK()
{
  delete http_client_;
}

const HttpClient * VK::getHttpClient() const noexcept
{
  return http_client_;
}

json VK::call(const string &method, const map<string, string> &params) const
{
  map<string, string> my_params(params);

  my_params.insert(pair<string, string>("access_token", access_token_));
  my_params.insert(pair<string, string>("v", v_));

  json j;

  while (true)
  {
    string data = http_client_->makeRequest("https://api.vk.com/method/" + method + "?" + http_client_->buildQuery(my_params));

    j = json::parse(data);

    if (j.find("error") != j.end())
    {
      if (j["error"]["error_code"] == 6)
      {
        this_thread::sleep_for(chrono::milliseconds(5000));
      }
      else
      {
        throw new runtime_error("Unhandled exception!");
      }
    }
    else
    {
      break;
    }
  }

  return j["response"];
}
