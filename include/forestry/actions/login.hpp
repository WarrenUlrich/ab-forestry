#pragma once

#include <Game/Core.hpp>

#include <util-ai/util-ai.hpp>

#include "../base_state.hpp"

namespace forestry {
class login : public util_ai::base_action<base_state> {
public:
  double utility(const base_state &ws) override {
    return Mainscreen::IsLoggedIn() ? -1.0 : 1.0;
  }

  void execute(base_state &ws) override {
    std::cout << "Logging in... ";
    if (!Login::LoginPlayer()) {
      std::cout << "Failed, retrying... ";
      if (!Login::LoginPlayer()) {
        std::cout << "Failed, terminating\n";
        Terminate = true;
        return;
      }
    }

    std::cout << "Success.\n";
  }
};
} // namespace skiller