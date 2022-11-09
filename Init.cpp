#include "lab_m1/Tema1/Tema1.h"
#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

const glm::vec3 LIME = glm::vec3(0.5f, 1, 0);
const glm::vec3 BROWN = glm::vec3(0.54f, 0.269f, 0.074f);
using namespace std;
using namespace m1;

void Tema1::InitVariables() {
    glm::ivec2 resolution = window->GetResolution();
    glm::vec3 corner = glm::vec3(0, 0, 0);
    colorLevel = LIME;
    triangleSide = 75;
    circleRadius = 25;
    grassHeight = 45;
    dirtHeight = 75;
    cx = corner.x;
    cy = corner.y;
    marginX = resolution.x;
    marginY = resolution.y;
    edgeBodyX = corner.x + 2 * triangleSide;
    edgeBodyY = corner.y + triangleSide / 2;
    edgeWingX = corner.x + 2 * triangleSide / 3;
    edgeWingY = corner.y + triangleSide / 6;
    translateX = 0;
    translateY = 0;
    bonusX = 0;
    bonusY = 0;
    scaleX = 1;
    scaleY = 1;
    numberOfLifes = 3;
    changeWingDirection = false;
    rotationWings = 0;
    nrOfDucks = 0;
    numberOfLifes = 3;
    maxAmmo = 3;
    killingSpree = 0;
    scoreMultiplier = 0;
    ducksOnScreen = 1;
}