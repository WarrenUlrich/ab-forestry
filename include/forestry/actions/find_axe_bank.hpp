#pragma once

#include <Game/Core.hpp>

#include <pathfinding/pathfinding.hpp>
#include <util-ai/util-ai.hpp>

#include "../base_state.hpp"

namespace forestry {
class find_axe_bank
    : public util_ai::base_action<base_state> {
public:
  double utility(const base_state &ws) override {
    if (!Mainscreen::IsLoggedIn())
      return -1.0;

    if (ws.current_axe.has_value() &&
        (ws.current_axe->in_inventory() ||
         ws.current_axe->equipped()))
      return -1.0;

    return 1.0;
  }

  void execute(base_state &ws) override {
    std::cout << "Finding axe... ";

    const auto bank_iter = pathfinding::bank::get_closest();
    if (bank_iter == pathfinding::bank::banks.end()) {
      std::cout << "No bank found.\n";
      return;
    }

    const auto &bank = *bank_iter;
    if (!bank->at()) {
      const auto player = Players::GetLocal();
      if (!player)
        return;

      const auto location = player.GetTile();
      const auto path = pathfinding::find_path(
          location, bank->pathfinding_tile);
      if (!path.has_value()) {
        std::cout << "Failed to find path.\n";
        return;
      }

      if (!pathfinding::walk_path(path.value())) {
        std::cout << "Failed.\n";
        return;
      }
    }

    if (!bank->open()) {
      std::cout << "Failed to open bank.\n";
      return;
    }

    if (!ws.current_axe.has_value()) {
      // Find best suitable axe.
      for (const auto &axe_ : axe::axes) {
        if (Inventory::Contains(axe_.name) &&
            axe_.can_use())
          ws.current_axe = axe_;
        else if (Bank::Contains(axe_.name) &&
                 axe_.can_use())
          ws.current_axe = axe_;
      }

      if (!ws.current_axe.has_value()) {
        std::cout << "No axe found, terminating.\n";
        Terminate = true;
        return;
      }
    }

    if (!Bank::Withdraw(ws.current_axe->name, 1, true)) {
      std::cout << "Failed to withdraw.\n";
      return;
    }

    while(Bank::IsOpen())
      Bank::Close();
    
    std::cout << "Found axe: " << ws.current_axe->name
              << '\n';
  }
};
} // namespace forestry