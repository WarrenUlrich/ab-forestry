#pragma once

#include <vector>

#include <Game/Core.hpp>

#include "tree_type.hpp"

namespace forestry {
class tree_instance {
public:
  tree_type type;
  Tile location;

  tree_instance() = default;
  ~tree_instance() = default;

  tree_instance(const tree_instance &other) = default;
  tree_instance(tree_instance &&other) = default;

  tree_instance &
  operator=(const tree_instance &other) = default;
  tree_instance &operator=(tree_instance &&other) = default;

  tree_instance(const tree_type &type, const Tile &location)
      : type(type), location(location) {}

  // TODO:
  static std::unordered_map<tree_type, std::vector<tree_instance>> instance_map;
};

// clang-format off
std::unordered_map<tree_type, std::vector<tree_instance>> tree_instance::instance_map = {
  {
    tree_type::normal,
    {
      // Grand Exchange Trees
      tree_instance(tree_type::normal, Tile(3143, 3494, 0)),
      tree_instance(tree_type::normal, Tile(3144, 3496, 0)),
      tree_instance(tree_type::normal, Tile(3146, 3501, 0)),
      tree_instance(tree_type::normal, Tile(3142, 3499, 0)),
      tree_instance(tree_type::normal, Tile(3146, 3501, 0)),
      // Varrock West Trees
      tree_instance(tree_type::normal, Tile(3149, 3458, 0)),
      tree_instance(tree_type::normal, Tile(3152, 3461, 0)),
      tree_instance(tree_type::normal, Tile(3155, 3458, 0)),
      tree_instance(tree_type::normal, Tile(3152, 3465, 0)),
      tree_instance(tree_type::normal, Tile(3160, 3459, 0)),
      tree_instance(tree_type::normal, Tile(3164, 3455, 0)),
    }
  },
  {
    tree_type::oak,
    {
      // Varrock West Oaks
      tree_instance(tree_type::oak, Tile(3168, 3421, 0)),
      tree_instance(tree_type::oak, Tile(3162, 3417, 0)),
      // Varrock East Oaks
      tree_instance(tree_type::oak, Tile(3280, 3431, 0)),
      tree_instance(tree_type::oak, Tile(3282, 3425, 0))
    }
  }
};
// clang-format on
} // namespace forestry