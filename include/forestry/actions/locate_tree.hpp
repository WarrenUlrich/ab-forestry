#pragma once

#include <Game/Core.hpp>

#include <util-ai/util-ai.hpp>

#include "../base_state.hpp"

namespace forestry {
class locate_tree
    : public util_ai::base_action<base_state> {
public:
  double utility(const base_state &ws) override {
    if (!Mainscreen::IsLoggedIn())
      return false;

    if (!ws.current_axe.has_value())
      return -1.0;

    if (ws.tree_cluster.has_value())
      return -1.0;

    return 1.0;
  }

  void execute(base_state &ws) override {
    std::cout << "Locating tree... ";
    const auto player = Players::GetLocal();
    if (!player) {
      std::cout << "No player.\n";
      return;
    }

    const auto location = player.GetTile();
    const auto tree_type = ws.selected_tree_type.value();
    const auto clusters =
        tree_location::tree_clusters[tree_type];

    tree_cluster closest_cluster;
    double min_distance =
        std::numeric_limits<double>::max();

    for (const auto &cluster : clusters) {
      const auto center = cluster.get_cluster_center();
      const auto distance = location.DistanceFrom(center);
      if (distance < min_distance) {
        min_distance = distance;
        closest_cluster = cluster;
      }
    }

    ws.tree_cluster = closest_cluster;
    std::cout << "Success.\n";
  }
};
} // namespace forestry