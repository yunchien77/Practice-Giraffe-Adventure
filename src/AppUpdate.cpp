#include "iostream"

#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

void App::Update() {

  // TODO: Add your own logics to finish the tasks in README.md

  /*
   *  Do not touch the code below as they serve the purpose for validating the
   * tasks, rendering the frame, and exiting the game.
   */

  // 1. Make the giraffe move with keyboard
  auto position = m_Giraffe->GetPosition();
  float speed = 5.0f;

  if (Util::Input::IsKeyPressed(Util::Keycode::W)) {
    position.y += speed;
  }
  if (Util::Input::IsKeyPressed(Util::Keycode::S)) {
    position.y -= speed;
  }
  if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
    position.x -= speed;
  }
  if (Util::Input::IsKeyPressed(Util::Keycode::D)) {
    position.x += speed;
  }

  m_Giraffe->SetPosition(position);

  // 2. Handle chest collision
  if (m_Giraffe->IfCollides(m_Chest) && m_Chest->GetVisibility()) {
    m_Chest->SetVisible(false);
  }

  // 3. Animate the bee
  auto beeAnimation = m_Bee->GetAnimation();
  beeAnimation->SetLooping(true); // 設置循環播放
  beeAnimation->Play();           // 開始播放動畫

  // 4. Handle door opening
  for (auto &door : m_Doors) {
    if (door->GetVisibility() && m_Giraffe->IfCollides(door)) {
      door->SetImage(GA_RESOURCE_DIR "/Image/Character/door_open.png");
    }
  }

  // 5. Handle countdown animation
  if (m_Phase == Phase::COUNTDOWN) {
    m_Ball->SetVisible(true);

    auto ballAnimation = m_Ball->GetAnimation();
    ballAnimation->Play(); // 開始播放動畫

    if (m_Ball->IfAnimationEnds()) {
      ballAnimation->Pause();
    }
  }

  if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) ||
      Util::Input::IfExit()) {
    m_CurrentState = State::END;
  }

  if (m_EnterDown) {
    if (!Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
      ValidTask();
    }
  }
  m_EnterDown = Util::Input::IsKeyPressed(Util::Keycode::RETURN);

  m_Root.Update();
}
