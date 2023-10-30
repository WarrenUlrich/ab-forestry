#include <filesystem>

#include <Game/Core.hpp>

#include <util-ai/util-ai.hpp>
#include <pathfinding/pathfinding.hpp>

#include <forestry/forestry.hpp>

void Setup() {
  ScriptInfo Info;
  Info.Name = "ab-forestry";
  Info.Description = "";
  Info.Version = "1.00";
  Info.Category = "Forestry";
  Info.Author = "Warren";
  Info.UID = "UID";
  Info.ForumPage = "forum.alpacabot.org";
  SetScriptInfo(Info);
}

bool OnStart() {
  const std::filesystem::path user_path =
      getenv("USERPROFILE");
  std::ifstream data(user_path / "AlpacaBot" /
                     "Collision Data" /
                     "collision_data.csv");
  pathfinding::load_collision_csv(data);
  return true;
}

auto forestry_agent = forestry::agent();
auto forestry_state = forestry::base_state();

bool Loop() {
  forestry_agent.decide_and_act(forestry_state);
  return true;
}

bool OnBreak() { return false; }

void OnEnd() {}