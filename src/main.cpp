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

forestry::base_state state = forestry::base_state();

util_ai::agent<forestry::base_state> agent{};

bool OnStart() {
  const std::filesystem::path user_path =
      getenv("USERPROFILE");
  std::ifstream data(user_path / "AlpacaBot" /
                     "Collision Data" /
                     "collision_data.csv");
  pathfinding::load_collision_csv(data);

  agent.add_action(std::make_unique<forestry::idle>());
  agent.add_action(std::make_unique<forestry::login>());
  return true;
}

bool Loop() {
  agent.decide_and_act(state);
  return true;
}

bool OnBreak() { return false; }

void OnEnd() {}