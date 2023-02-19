#include "lab_m1/Tema1/Tema1.h"
#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"
#include "lab_m1/Tema1/Defines.h"

using namespace std;
using namespace m1;

void Tema1::InitVariables() {
    isStarting = true;
    isStats = false;
    glm::ivec2 resolution = window->GetResolution();
    colorLevel = LIME;
    posXCursor = 250, posYCursor = 250;
    triangleSide = 75;
    circleRadius = 25;
    grassHeight = 45;
    dirtHeight = 75;
    diamondLength1 = 12.5, diamondLength2 = 25;
    cx = 0;
    cy = 0;
    marginX = resolution.x;
    marginY = resolution.y;
    edgeBodyX =  2 * triangleSide;
    edgeBodyY =  triangleSide / 2;
    edgeWingX =  2 * triangleSide / 3;
    edgeWingY =  triangleSide / 6;
    translateX = 0;
    translateY = 0;
    scaleX = 1;
    scaleY = 1;
    numberOfLifes = 3;
    changeWingDirection = false;
    rotationWings = 0;

    duck_counter = 0;
    nrOfDucks = 0;
    numberOfLifes = 3;
    maxAmmo = 3;
    score = 0;
    killingSpree = 0;
    scoreMultiplier = 0;
    ducksOnScreen = 1;
    barLength = 151;
    barHeight = 25;
    wireframeLength = 206;
    bigDuckHP = 5;
    BIG_DUCK = false;
    colorBackground = DARK_BLUE;
    posXBossBar = 300;
    posYBossBar = 670;
    bossBarScaling = 3.05f;
    scalingFactor = 25;

    initSpeedVariables();

    for (int i = 0; i < NUMBER_OF_BUTTONS; i++) {
        colorButton[i] = LIME;
    }
    colorBackButton = LIME;
    buttonName[0] = "QUIT";
    buttonName[1] = "STATS";
    buttonName[2] = "START";

    initTimeVariables();
}

void Tema1::initTimeVariables() {
    timeOnScreen = 8.0f;
    flashTime = 0;
    timeDuck = 0;
    slowTime = 0;
    lastBounce = 0;
    changeDirection = 0;
    timeSpent = 0;
}

void Tema1::initSpeedVariables() {
    duckSpeed = 140;
    wingSpeed = 2.8f;
    reducedSpeed = 50.0f;
    wingTurnTime = 0.4f;
}