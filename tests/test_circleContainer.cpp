#include "circle.h"
#include "circleContainer.h"
#include <SFML/Graphics.hpp>
#include <catch2/catch_all.hpp>

#include <vector>

TEST_CASE("CircleContainer add and delete circles", "[CircleContainer]") {
  CircleContainer container("container");
  Circle circle("circle", true, 100.f, 10.f, 200.f, 300.f, 1.f, 1.f, 138, 206,
                255);

  container.addCircle(circle);
  REQUIRE(container.getSize() == 1);

  container.delCircle(circle.getName());
  REQUIRE(container.getSize() == 0);
}

TEST_CASE("CircleContainer add circles from vector", "[CircleContainer]") {
  CircleContainer container("container");
  Circle circle1("circle1", true, 100.f, 10.f, 200.f, 300.f, 1.f, 1.f, 138, 206,
                 255);
  Circle circle2("circle2", true, 100.f, 10.f, 200.f, 300.f, 1.f, 1.f, 138, 206,
                 255);
  std::vector<Circle> circles = {circle1, circle2};

  container.addCirclesFromVector(circles);
  REQUIRE(container.getSize() == 2);
}
