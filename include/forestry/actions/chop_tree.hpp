#pragma once

#include <Game/Core.hpp>

#include <util-ai/util-ai.hpp>

#include "../base_state.hpp"
#include "../constants.hpp"

namespace forestry {
class chop_tree : public util_ai::base_action<base_state> {
public:
  double utility(const base_state &ws) override {
    if (!Mainscreen::IsLoggedIn())
      return -1.0;

    if (Inventory::IsFull())
      return -1.0;

    const auto player = Players::GetLocal();
    if (!player)
      return -1.0;

    if (player.GetAnimationID() == chopping_anim_id)
      return -1.0;

    if (!ws.current_axe.has_value())
      return -1.0;

    if (!(ws.current_axe->in_inventory() ||
          ws.current_axe->equipped()))
      return -1.0;

    if (!ws.selected_tree_type.has_value())
      return -1.0;

    if (!ws.tree_cluster.has_value())
      return -1.0;

    return 1.0;
  }

  void execute(base_state &ws) override {
    const auto player = Players::GetLocal();
    if (!player) {
      std::cout << "No player.\n";
      return;
    }

    const auto location = player.GetTile();

    const auto cluster_location =
        ws.tree_cluster->get_cluster_center();

    const auto cluster_area =
        ws.tree_cluster->get_bounding_area();
    if (!cluster_area.Contains(location)) {
      const auto dest =
          cluster_area.GetProfileHybridRandomTile();
      const auto dest_walkable =
          pathfinding::find_walkable(dest, 2);
      if (!dest_walkable.has_value()) {
        std::cout << "No walkable tile.\n";
        return;
      }

      const auto path = pathfinding::find_path(
          location, dest_walkable.value());

      if (!path.has_value()) {
        std::cout << "No path found.\n";
        return;
      }

      if (!pathfinding::walk_path(path.value())) {
        std::cout << "Failed to walk path.\n";
        return;
      }
    }

    if (!Mainscreen::IsAnimating()) {
      const auto objects = ws.tree_cluster->get_objects();
      if (objects.empty()) {
        std::cout << "No trees to cut.\n";
        return;
      }

      const auto &obj = objects.front();
      if (!obj.Interact("Chop down")) {
        std::cout << "Failed to interact.\n";
        return;
      }

      if (!WaitFunc(1500, 50, Mainscreen::IsAnimating)) {
        std::cout << "Failed to start chopping.\n";
        return;
      }
    }

    std::cout << "Chopping...\n";
  }
};
} // namespace forestry