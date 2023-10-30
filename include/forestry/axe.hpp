#pragma once

#include <cstdint>
#include <string>

#include <Game/Core.hpp>

namespace forestry {
class axe {
public:
  std::string name;
  std::int32_t required_level;

  axe() = default;
  ~axe() = default;

  axe(const axe &other) = default;
  axe(axe &&other) = default;

  axe &operator=(const axe &other) = default;
  axe &operator=(axe &&other) = default;

  axe(const std::string &name, std::int32_t required_level)
      : name(name), required_level(required_level) {}

  bool in_bank() const { return Bank::Contains(name); }

  bool in_inventory() const {
    return Inventory::Contains(name);
  }

  bool equipped() const {
    const auto weapon =
        Equipment::GetItem(Equipment::WEAPON);
    if (!weapon)
      return false;

    return weapon.GetName() == name;
  }
  bool can_use() const {
    return Stats::GetCurrentLevel(Stats::WOODCUTTING) >=
           required_level;
  }

  bool can_equip() const {
    return Stats::GetCurrentLevel(Stats::WOODCUTTING) >=
           (required_level - 1);
  }

  static std::vector<axe> axes;
};

std::vector<axe> axe::axes = {
    axe("Bronze axe", 1),   axe("Iron axe", 1),
    axe("Steel axe", 6),    axe("Black axe", 11),
    axe("Mithril axe", 21), axe("Adamant axe", 31),
    axe("Rune axe", 41)};
} // namespace forestry