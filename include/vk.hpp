#ifndef VK_API_HPP_INCLUDED
#define VK_API_HPP_INCLUDED

#include <string>
#include <map>
#include <nlohmann/json.hpp>
#include <http-client/http-client.hpp>

namespace vk
{
  class VK
  {
  public:
    VK(const std::string &v = "5.80");
    ~VK();
    const http_client::HttpClient * getHttpClient() const noexcept;
    virtual nlohmann::json call(const std::string &method, const std::map<std::string, std::string> &params = {}) const = 0;

  protected:
    const http_client::HttpClient *http_client_;
    const std::string v_;
  };
}

#endif
