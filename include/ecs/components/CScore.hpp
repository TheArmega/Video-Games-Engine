#include "ecs/core/Component.h"

class CScore : public Component {

public:
  float score = 0;
  CScore() {}
  CScore(float _score) : score(_score) {}
};
