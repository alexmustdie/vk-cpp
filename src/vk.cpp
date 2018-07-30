#include <vk/vk.hpp>

using namespace vk;
using namespace http_client;

VK::VK(const std::string &v):
  http_client_(new HttpClient),
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
