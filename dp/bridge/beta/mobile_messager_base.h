#ifndef BRIDGE_BETA_MOBILE_MESSAGER_BASE_H
#define BRIDGE_BETA_MOBILE_MESSAGER_BASE_H

#include "messager.h"
namespace beta {
class MobileMessagerBase : public Messager {
 public:
  void PlaySound() override;
  void DrawShape() override;
  void WriteText() override;
  void Connect() override;
};
}  // namespace beta
#endif