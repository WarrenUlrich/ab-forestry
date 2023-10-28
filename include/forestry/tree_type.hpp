#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace forestry {
class tree_type {
public:
  std::string name;
  std::int32_t required_level;

  tree_type() = default;
  ~tree_type() = default;

  tree_type(const tree_type &other)
      : name(other.name),
        required_level(other.required_level) {}

  tree_type(tree_type &&other)
      : name(std::move(other.name)),
        required_level(
            std::exchange(other.required_level, -1)) {}

  tree_type(const std::string &name,
            std::int32_t required_level)
      : name(name), required_level(required_level) {}

  tree_type &operator=(const tree_type &other) {
    if (this != &other) {
      name = other.name;
      required_level = other.required_level;
    }

    return *this;
  }

  tree_type &operator=(tree_type &&other) {
    if (this != &other) {
      name = std::move(other.name);
      required_level =
          std::exchange(other.required_level, -1);
    }

    return *this;
  }

  bool operator==(const tree_type &other) const {
    return name == other.name &&
           required_level == other.required_level;
  }

  bool operator!=(const tree_type &other) const {
    return !(*this == other);
  }

  static tree_type normal;
  static tree_type oak;
};

tree_type tree_type::normal = tree_type("Tree", 1);
tree_type tree_type::oak = tree_type("Oak tree", 15);

} // namespace forestry

namespace std {
template <> struct hash<forestry::tree_type> {
  std::size_t
  operator()(const forestry::tree_type &t) const {
    std::size_t h1 = std::hash<std::string>{}(t.name);
    std::size_t h2 =
        std::hash<std::int32_t>{}(t.required_level);
    // Combine the hashes of name and required_level
    return h1 ^
           (h2 << 1); // or use another combining technique
  }
};
} // namespace std