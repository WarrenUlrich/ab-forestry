#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include <Game/Core.hpp>

#include "axe.hpp"
#include "tree_type.hpp"

namespace forestry {
class base_state {
public:
  std::optional<axe> current_axe;
  std::optional<tree_type> current_tree_type;
  std::optional<tree_instance> found_tree_instance;
  
};

template <typename T>
concept State = std::same_as<T, base_state>;
} // namespace forestry