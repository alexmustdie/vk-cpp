#ifndef VKAPI_BASE_TYPES_HPP
#define VKAPI_BASE_TYPES_HPP

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace vk
{
  struct message_t
  {
    id_t id;
    id_t from_id;
    std::string text;
    nlohmann::json payload;
    nlohmann::json attachments;
  };

  struct button_t
  {
    std::string type;
    nlohmann::json payload;
    std::string label;
    std::string color;

    button_t(const nlohmann::json &payload, const std::string &label, const std::string color = "default"):
      type("text"),
      payload(payload),
      label(label),
      color(color)
    {}
  };

  struct keyboard_t
  {
    bool one_time;
    std::vector<button_t> buttons;

    keyboard_t():
      one_time(true)
    {}

    keyboard_t(const button_t &button):
      one_time(true)
    {
      addButton(button);
    }

    void addButton(const button_t &button) noexcept
    {
      buttons.push_back(button);
    }

    nlohmann::json json() const noexcept
    {
      nlohmann::json keyboard;

      keyboard["one_time"] = one_time;

      for (size_t i = 0; i < buttons.size(); i++)
      {
        keyboard["buttons"][i][0]["action"]["type"] = buttons[i].type;
        keyboard["buttons"][i][0]["action"]["payload"] = buttons[i].payload.dump();
        keyboard["buttons"][i][0]["action"]["label"] = buttons[i].label;
        keyboard["buttons"][i][0]["color"] = buttons[i].color;
      }

      return keyboard;
    }
  };
}

#endif
