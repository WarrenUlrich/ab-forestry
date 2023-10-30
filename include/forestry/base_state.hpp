#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include <Game/Core.hpp>

#include "axe.hpp"
#include "tree_type.hpp"
#include "tree_location.hpp"

namespace forestry {
class base_state {
public:
  std::optional<axe> current_axe;
  std::optional<tree_type> selected_tree_type;
  std::optional<tree_cluster> tree_cluster;
};

template <typename T>
concept State = std::same_as<T, base_state>;
} // namespace forestry