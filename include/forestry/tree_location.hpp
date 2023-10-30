#pragma once

#include <unordered_map>
#include <utility>
#include <vector>

#include <Game/Core.hpp>

#include "tree_type.hpp"

namespace forestry {
class tree_cluster;

class tree_location {
public:
  tree_type type;
  Tile location;

  tree_location() = default;
  ~tree_location() = default;

  tree_location(const tree_location &other) = default;
  tree_location(tree_location &&other) = default;

  tree_location &
  operator=(const tree_location &other) = default;
  tree_location &operator=(tree_location &&other) = default;

  tree_location(const tree_type &type, const Tile &location)
      : type(type), location(location) {}

  static std::unordered_map<tree_type,
                            std::vector<tree_cluster>>
      tree_clusters;
};

class tree_cluster {
public:
  std::vector<tree_location> trees;
  Area a;
  
  tree_cluster() = default;
  ~tree_cluster() = default;

  tree_cluster(const tree_cluster &other) = default;
  tree_cluster(tree_cluster &&other) = default;

  tree_cluster &
  operator=(const tree_cluster &other) = default;
  tree_cluster &operator=(tree_cluster &other) = default;

  tree_cluster(const std::vector<tree_location> trees)
      : trees(trees) {}

  Tile get_cluster_center() const {
    std::int64_t total_x = 0, total_y = 0;
    for (const auto &tree : trees) {
      total_x += tree.location.X;
      total_y += tree.location.Y;
    }

    return Tile(total_x / trees.size(),
                total_y / trees.size(),
                trees.front().location.Plane);
  }

  tree_location get_closest_tree(const Tile &tile) const {
    auto it = std::min_element(
        trees.begin(), trees.end(),
        [&tile](const tree_location &a,
                const tree_location &b) {
          return a.location.DistanceFrom(tile) <
                 b.location.DistanceFrom(tile);
        });
    return (it != trees.end()) ? *it : tree_location();
  }

  bool is_within_area(const Area &area) const {
    return std::all_of(trees.begin(), trees.end(),
                       [&area](const tree_location &tree) {
                         return area.Contains(
                             tree.location);
                       });
  }

  std::size_t get_tree_count() const {
    return trees.size();
  }
};

// clang-format off
std::unordered_map<tree_type, std::vector<tree_cluster>> tree_location::tree_clusters = {
  {
    tree_type::normal,
    {
      // Grand Exchange Trees
      tree_cluster({
        tree_location(tree_type::normal, Tile(3143, 3494, 0)),
        tree_location(tree_type::normal, Tile(3144, 3496, 0)),
        tree_location(tree_type::normal, Tile(3146, 3501, 0)),
        tree_location(tree_type::normal, Tile(3142, 3499, 0)),
        tree_location(tree_type::normal, Tile(3146, 3501, 0)),
      }),
      // Varrock West Trees
      tree_cluster({
        tree_location(tree_type::normal, Tile(3149, 3458, 0)),
        tree_location(tree_type::normal, Tile(3152, 3461, 0)),
        tree_location(tree_type::normal, Tile(3155, 3458, 0)),
        tree_location(tree_type::normal, Tile(3152, 3465, 0)),
        tree_location(tree_type::normal, Tile(3160, 3459, 0)),
        tree_location(tree_type::normal, Tile(3164, 3455, 0)),
      }),
    }
  },
  {
    tree_type::oak,
    {
      // Varrock West Oaks
      tree_cluster({
        tree_location(tree_type::oak, Tile(3168, 3421, 0)),
        tree_location(tree_type::oak, Tile(3162, 3417, 0)),
      }),
      // Varrock East Oaks
      tree_cluster({
        tree_location(tree_type::oak, Tile(3280, 3431, 0)),
        tree_location(tree_type::oak, Tile(3282, 3425, 0)),
      }),
    }
  },
};
// clang-format on
// clang-format off
// std::unordered_map<tree_type, std::vector<tree_location>> tree_location::instance_map = {
//   {
//     tree_type::normal,
//     {
//       // Grand Exchange Trees
//       tree_location(tree_type::normal, Tile(3143, 3494, 0)),
//       tree_location(tree_type::normal, Tile(3144, 3496, 0)),
//       tree_location(tree_type::normal, Tile(3146, 3501, 0)),
//       tree_location(tree_type::normal, Tile(3142, 3499, 0)),
//       tree_location(tree_type::normal, Tile(3146, 3501, 0)),
//       // Varrock West Trees
//       tree_location(tree_type::normal, Tile(3149, 3458, 0)),
//       tree_location(tree_type::normal, Tile(3152, 3461, 0)),
//       tree_location(tree_type::normal, Tile(3155, 3458, 0)),
//       tree_location(tree_type::normal, Tile(3152, 3465, 0)),
//       tree_location(tree_type::normal, Tile(3160, 3459, 0)),
//       tree_location(tree_type::normal, Tile(3164, 3455, 0)),
//     }
//   },
//   {
//     tree_type::oak,
//     {
//       // Varrock West Oaks
//       tree_location(tree_type::oak, Tile(3168, 3421, 0)),
//       tree_location(tree_type::oak, Tile(3162, 3417, 0)),
//       // Varrock East Oaks
//       tree_location(tree_type::oak, Tile(3280, 3431, 0)),
//       tree_location(tree_type::oak, Tile(3282, 3425, 0))
//     }
//   }
// };
// clang-format on
} // namespace forestry