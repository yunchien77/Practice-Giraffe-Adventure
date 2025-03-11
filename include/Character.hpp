#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "iostream"
#include <string>

#include "Util/GameObject.hpp"

class Character : public Util::GameObject {
public:
  explicit Character(const std::string &ImagePath);

  Character(const Character &) = delete;

  Character(Character &&) = delete;

  Character &operator=(const Character &) = delete;

  Character &operator=(Character &&) = delete;

  [[nodiscard]] const std::string &GetImagePath() const { return m_ImagePath; }

  [[nodiscard]] const glm::vec2 &GetPosition() const {
    return m_Transform.translation;
  }

  [[nodiscard]] bool GetVisibility() const { return m_Visible; }

  void SetImage(const std::string &ImagePath);

  void SetPosition(const glm::vec2 &Position) {
    m_Transform.translation = Position;
  }

  // TODO: Implement the collision detection
  [[nodiscard]] bool IfCollides(const std::shared_ptr<Character> &other) const {
    // 檢查傳入的指針是否有效
    if (!other) {
      std::cout << "111";
      return false;
    }

    // 獲取兩個物體的位置
    const glm::vec2 &pos1 = m_Transform.translation;
    const glm::vec2 &pos2 = other->GetPosition();

    auto size1 = m_Drawable->GetSize();
    auto size2 = other->m_Drawable->GetSize();

    // 計算每個物體的邊界
    float left1 = pos1.x - size1.x / 2;
    float right1 = pos1.x + size1.x / 2;
    float top1 = pos1.y + size1.y / 2;
    float bottom1 = pos1.y - size1.y / 2;

    float left2 = pos2.x - size2.x / 2;
    float right2 = pos2.x + size2.x / 2;
    float top2 = pos2.y + size2.y / 2;
    float bottom2 = pos2.y - size2.y / 2;

    bool hasCollision = (left1 <= right2 && // 物體1的左邊在物體2的右邊之前
                         right1 >= left2 && // 物體1的右邊在物體2的左邊之後
                         bottom1 <= top2 && // 物體1的底部在物體2的頂部之下
                         top1 >= bottom2); // 物體1的頂部在物體2的底部之上

    // if (hasCollision) {
    //   std::cout << "collision? " << hasCollision << std::endl;
    //   other->SetVisible(false);
    // }
    return hasCollision;
  }

  // TODO: Add and implement more methods and properties as needed to finish
  // Giraffe Adventure.

private:
  void ResetPosition() { m_Transform.translation = {0, 0}; }

  std::string m_ImagePath;
};

#endif // CHARACTER_HPP
