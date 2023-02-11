#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"   
#include "lab_m1/Tema1/object2D.h"
#include "lab_m1/Tema1/Defines.h"

using namespace std;
using namespace m1;


bool ok = false;

Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}
// TODO: implementat text for buttons and score (FreeType library)
// TODO: save highscore in a notepad (and other stats)
// TODO: 3 - 4 buttons: 1 -> Start ; 2 -> Stats ; 3 (optional - HARD) -> Settings ; 4 -> Quit 
// TODO: special animation for duck death
// TODO: end-game screen for win/lose
// TODO: divide Tema1.cpp into multiple cpp files
// DONE: hide cursor
// DONE: show cursor in menu aswell
// BUG:  full-screen mode doesn't work in menu.
// BUG:  max-speed ducks crash their head in the corners (sometimes)
  
void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorBackground.x, colorBackground.y, colorBackground.z, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}
void Tema1::CreateMeshes() {

    glm::vec3 corner = glm::vec3(0, 0, 0);
    glm::ivec2 resolution = window->GetResolution();

    Mesh* triangle1 = object2D::CreateTriangle("triangle1", corner, triangleSide, BROWN, true);
    AddMeshToList(triangle1);

    Mesh* triangle2 = object2D::CreateTriangle("triangle2", corner, triangleSide / 3, BROWN, true);
    AddMeshToList(triangle2);

    Mesh* triangle4 = object2D::CreateTriangle("triangle4", corner, triangleSide / 7, YELLOW, true);
    AddMeshToList(triangle4);

    Mesh* circle1 = object2D::CreateCircle("circle1", corner, circleRadius, GREEN, true);
    AddMeshToList(circle1);

    Mesh* dirt = object2D::CreateRectangle("dirt", corner, resolution.x, dirtHeight, DIRT, true);
    AddMeshToList(dirt);

    Mesh* grass = object2D::CreateRectangle("grass", corner, resolution.x, grassHeight, LIGHT_GREEN, true);
    AddMeshToList(grass);

    Mesh* target = object2D::CreateCircle("target", corner, circleRadius / 3, LIME, false);
    AddMeshToList(target);

    Mesh* targetCross = object2D::CreateCross("targetCross", corner, circleRadius / 3, RED);
    AddMeshToList(targetCross);

    Mesh* ammo = object2D::CreateRectangle("ammo", corner, barLength / 10, barHeight, GREEN, true);
    AddMeshToList(ammo);

    Mesh* wireframe = object2D::CreateRectangle("wireframe", corner, wireframeLength, 2 * barHeight, WHITE);
    AddMeshToList(wireframe);

    Mesh* loadingScore = object2D::CreateRectangle("loadingScore", corner, 5, 2 * barHeight, ORANGE, true);
    AddMeshToList(loadingScore);

    Mesh* Rectangle = object2D::CreateRectangle("rectangle", corner, 1, 1, ORANGE, true);
    AddMeshToList(Rectangle);

    Mesh* bar = object2D::CreateBar("bar", corner, barLength, barHeight, WHITE);
    AddMeshToList(bar);

    Mesh* button = object2D::CreateBar("button", corner, barLength, barHeight, WHITE, true);
    AddMeshToList(button);

    Mesh* diamond = object2D::CreateDiamond("diamond", corner, diamondLength1, diamondLength2, CYAN, LIGHT_BLUE, BLUE, true);
    AddMeshToList(diamond);

}
void Tema1::startingWindow() {
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(posXCursor, posYCursor);
    RenderMesh2D(meshes["targetCross"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(posXCursor, posYCursor);
    RenderMesh2D(meshes["target"], shaders["VertexColor"], modelMatrix);

    for (int i = 0; i < NUMBER_OF_BUTTONS; ++i) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(marginX / 2 - 452 / 2, marginY - i * marginY / NUMBER_OF_BUTTONS - 50);
        // 151 * 3 ; 25 * 3; 
        modelMatrix *= transform2D::Scale(3, 3);
        RenderMesh2D(meshes["button"], modelMatrix, colorButton[i]);
    }
}
void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    window->HidePointer();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 200));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    srand(time(NULL));
    InitVariables();
    CreateMeshes();
}
void Tema1::RenderBackground() {

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(posXCursor, posYCursor);
    RenderMesh2D(meshes["targetCross"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(posXCursor, posYCursor);
    RenderMesh2D(meshes["target"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["dirt"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, dirtHeight);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(marginX - 350, marginY - 150);
    RenderMesh2D(meshes["wireframe"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(marginX - 350, marginY - 150);
    modelMatrix *= transform2D::Scale(1 + 8 * nrOfDucks, 1);
    RenderMesh2D(meshes["loadingScore"], modelMatrix, colorLevel);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(50, marginY - 101);
    RenderMesh2D(meshes["bar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(50, marginY - 151);
    RenderMesh2D(meshes["bar"], shaders["VertexColor"], modelMatrix);

}
void Tema1::WingAnimation(float deltaTimeSeconds) {
    if (rotationWings >= wingTurnTime) {
        changeWingDirection = true;
    }
    if (rotationWings <= -wingTurnTime) {
        changeWingDirection = false;
    }
    if (changeWingDirection) {
        rotationWings -= deltaTimeSeconds * wingSpeed;
    }
    else {
        rotationWings += deltaTimeSeconds * wingSpeed;
    }
}
void Tema1::DuckAnimation(float deltaTimeSeconds) {

    // capu la rata
    for (int i = 0; i < ducksOnScreen; ++i) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(posHeadX[i], posHeadY[i]);
        if (BIG_DUCK) {
            modelMatrix *= transform2D::Scale(2, 2);
        }
        RenderMesh2D(meshes["circle1"], shaders["VertexColor"], modelMatrix);

        // corpu la rata
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(posHeadX[i] - circleRadius * cos(angleTurn[i]) - 2 * triangleSide,
                                              posHeadY[i] - circleRadius * sin(angleTurn[i]) - triangleSide / 2);
        if (BIG_DUCK) {
            modelMatrix *= transform2D::Scale(2, 2);
        }
        modelMatrix *= transform2D::Translate(edgeBodyX, edgeBodyY);
        modelMatrix *= transform2D::Rotate(angleTurn[i]);
        modelMatrix *= transform2D::Translate(-edgeBodyX, -edgeBodyY);

        RenderMesh2D(meshes["triangle1"], modelMatrix, color[i]);

        WingAnimation(deltaTimeSeconds);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(posHeadX[i] - (circleRadius + triangleSide - triangleSide / 6) * cos(angleTurn[i]),
                                              posHeadY[i] - (circleRadius + triangleSide - triangleSide / 6) * sin(angleTurn[i]));
        if (BIG_DUCK) {
            modelMatrix *= transform2D::Scale(2, 2);
        }
        modelMatrix *= transform2D::Rotate(PI / 2 + angleTurn[i]);
        modelMatrix *= transform2D::Translate(cx, cy);
        modelMatrix *= transform2D::Rotate(rotationWings);
        modelMatrix *= transform2D::Translate(-cx, -cy);

        RenderMesh2D(meshes["triangle2"], modelMatrix, color[i]);

        // aripa la rata
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(posHeadX[i] - (circleRadius + triangleSide + triangleSide / 6) * cos(angleTurn[i]),
            posHeadY[i] - (circleRadius + triangleSide + triangleSide / 6) * sin(angleTurn[i]));
        if (BIG_DUCK) {
            modelMatrix *= transform2D::Scale(2, 2);
        }
        modelMatrix *= transform2D::Rotate(-PI / 2 + angleTurn[i]);
        modelMatrix *= transform2D::Translate(cx, cy);
        modelMatrix *= transform2D::Rotate(-rotationWings);
        modelMatrix *= transform2D::Translate(-cx, -cy);
        RenderMesh2D(meshes["triangle2"], modelMatrix, color[i]);

        // ciocu la rata
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(posHeadX[i] + circleRadius * cos(angleTurn[i]), posHeadY[i] +
                        circleRadius * sin(angleTurn[i]));
        if (BIG_DUCK) {
            modelMatrix *= transform2D::Scale(2, 2);
        }
        modelMatrix *= transform2D::Translate(cx, cy);
        modelMatrix *= transform2D::Rotate(angleTurn[i]);
        modelMatrix *= transform2D::Translate(-cx, -cy);
        RenderMesh2D(meshes["triangle4"], shaders["VertexColor"], modelMatrix);
    }
}
void Tema1::CheckUpperMargin(float timeD) {

    // MARGINE SUS
    for (int i = 0; i < ducksOnScreen; ++i) {
        if (posHeadY[i] + circleRadius > marginY) {
            angleTurn[i] = 2 * PI - angleTurn[i];
            lastBounce = timeD;
        }
    }
}
void Tema1::CheckMargins(float timeD) {

    if (timeD - lastBounce < EPS)
        return;
    if (!flyAway) {
        CheckUpperMargin(timeD);
    }
    // MARGINE DREAPTA
    for (int i = 0; i < ducksOnScreen; ++i) {
        if (posHeadX[i] + circleRadius > marginX) {
            angleTurn[i] = PI - angleTurn[i];
            lastBounce = timeD;
        }
    }
    // MARGINE STANGA
    for (int i = 0; i < ducksOnScreen; ++i) {
        if (posHeadX[i] < 0) {
            angleTurn[i] = PI - angleTurn[i];
            lastBounce = timeD;
        }
    }
    // MARGINE JOS
    for (int i = 0; i < ducksOnScreen; ++i) {
        if (posHeadY[i] - circleRadius < 0) {
            angleTurn[i] = 2 * PI - angleTurn[i];
            lastBounce = timeD;
        }
    }

}
bool Tema1::CheckAllDucks() {
    for (int i = 0; i < ducksOnScreen; ++i) {
        if (!deadDuck[i] || posHeadY[i] > 0) {
            return false;
         }
    }
    return true;
}
void Tema1::NewColorLevel() {
    // La fiecare 10 puncte acumulate, bara de scor va capata o noua culoare

    // LEVEL 1 
    if (colorLevel == LIME) {
        colorLevel = GREEN;
        return;
    }
    // LEVEL 2
    if (colorLevel == GREEN) {
        colorLevel = YELLOW;
        return;
    }
    // LEVEL 3
    if (colorLevel == YELLOW) {
        colorLevel = ORANGE;
        return;
    }
    // LEVEL 4
    if (colorLevel == ORANGE) {
        colorLevel = RED;
        return;
    }
    // LEVEL 5
    if (colorLevel == RED) {
        colorLevel = ORCHID; 
        return;
    }
    // LEVEL 6
    if (colorLevel == ORCHID) {
        colorLevel = BLUE;
        return;
    }
    // BOSS FIGHT
    if (colorLevel == BLUE) {
        triangleSide = triangleSide * 2;
        circleRadius = circleRadius * 2;
        BIG_DUCK = true;
        duckSpeed /= 2;
        colorLevel = BLACK;
        ducksOnScreenCopy = ducksOnScreen;
        ducksOnScreen = 1;
        return;
    }
    // BACK TO LEVEL 1
    if (colorLevel == BLACK) {
        BIG_DUCK = false;
        duckSpeed = min(duckSpeed * 2.0f, DUCK_SPEED_LIMIT);
        triangleSide = triangleSide / 2.0f;
        circleRadius = circleRadius / 2.0f;
        ducksOnScreen = ducksOnScreenCopy;
        ducksOnScreen++;
        colorLevel = LIME;
    }
}
void Tema1::RenderFreezeTime(float timeRemaining) {
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(marginX - 350, marginY - 230);
    RenderMesh2D(meshes["wireframe"], modelMatrix, WHITE);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(marginX - 350, marginY - 230);
    modelMatrix *= transform2D::Scale(timeRemaining * 2, 1);
    RenderMesh2D(meshes["loadingScore"], modelMatrix, ORCHID);
}
void Tema1::RandomDuckEffect(int i) {
    int randomDuck = rand() % 20;
    if (randomDuck <= 8) {
        color[i] = BROWN;
    }
    if (randomDuck > 8 && randomDuck < 16) {
        color[i] = WHITE;
    }
    if (randomDuck == 16 || randomDuck == 17) {
        color[i] = LIME;
    }
    if (randomDuck == 18) {
        color[i] = RED;
    }
    if (randomDuck == 19) {
        color[i] = CYAN;
    }
}
void Tema1::CheckBonusEffects(int i) {
    if (color[i] == LIME) {
        maxAmmo = min(maxAmmo + 1, MAX_AMMO_LIMIT);
    }
    if (color[i] == RED) {
        numberOfLifes = min(numberOfLifes + 1, MAX_HEALTH_LIMIT);
    }
    if (color[i] == CYAN) {
        freezeTime = true;
        if (slowTime <= 0.0f) {
            duckSpeed = duckSpeed / 2.0f;
            wingSpeed = wingSpeed / 2.0f;
        }
        slowTime = 20.0f;
    }
}
void Tema1::RenderInfo() {
    for (int i = 0; i < Ammo; ++i) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(50 + i * 20, marginY - 125.5);
        RenderMesh2D(meshes["ammo"], shaders["VertexColor"], modelMatrix);
    }
    for (int i = 0; i < numberOfLifes; ++i) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(64 + i * 30, marginY - 164);
        modelMatrix *= transform2D::Scale(0.5, 0.5);
        RenderMesh2D(meshes["circle1"], modelMatrix, glm::vec3(1, 0, 0));
    }
}
bool Tema1::RescaleDiamond(float timeScale) {
    int j = 1;
    for (float i = 0.5; i <= 30.0; i = i + 0.5) {
         if (timeScale < i && j % 2 == 1)
            return true;
         if (timeScale < i && j % 2 == 0)
             return false;
         ++j;
    }
    return true;
}
void Tema1::CheckKillingSpree(float timeToScale) {
   
   bool rescale = RescaleDiamond(timeToScale);
   int numberOfDiamonds = min(killingSpree / 5, 5);
   for (int i = 0; i < numberOfDiamonds; ++i) {
            modelMatrix = glm::mat3(1);
            // de la marginea din dreapta scadem cei 420 pixeli iar pt fiecare diamant lasam 2 * L2 + 5 pixeli spatiu
            modelMatrix *= transform2D::Translate(marginX - 420 - i * (diamondLength2 * 2 + 20), marginY - 120);
            if (rescale) {
                modelMatrix *= transform2D::Translate(diamondLength2, 0);
                modelMatrix *= transform2D::Scale(1.25, 1.25);
                modelMatrix *= transform2D::Translate(-diamondLength2, 0);
            }
            else {
                modelMatrix *= transform2D::Translate(diamondLength2, 0);
                modelMatrix *= transform2D::Scale(0.8, 0.8);
                modelMatrix *= transform2D::Translate(-diamondLength2, 0);
            }
            RenderMesh2D(meshes["diamond"], shaders["VertexColor"], modelMatrix);
        }
}
void Tema1::ResetVariables() {
    if (BIG_DUCK) {
        nrOfDucks += 5;
        killingSpree++;
        nrOfDucks += killingSpree / 5;
        deadDuck[0] = false;
        return; 
    }
    for (int i = 0; i < ducksOnScreen; ++i) {
        if (deadDuck[i]) {
            nrOfDucks++;
            killingSpree++;
            CheckBonusEffects(i);
        }
        deadDuck[i] = false;
        if (nrOfDucks % 5 == 0) {
            duckSpeed = min(duckSpeed + duckSpeed / 5, DUCK_SPEED_LIMIT);
            wingSpeed = min(wingSpeed + wingSpeed / 5, WING_SPEED_LIMIT);
        }
        nrOfDucks += killingSpree / 5;
    }
}
void Tema1::RandomMovement(float deltaTimeSeconds) {
    for (int i = 0; i < ducksOnScreen; ++i) {
         angleTurn[i] += 0.4 * randomAngle * deltaTimeSeconds;
    }
    if (fabs(changeDirection - 2.0f) < EPS) {
        for (int i = 0; i < ducksOnScreen; ++i) {
            randomAngle = (rand() % 3) - 1; // (generez -1, 0 sau 1)
        }
        changeDirection = 0;
    }
}
void Tema1::SlowTimeEffect() {
    if (slowTime > 0.0f) {
        RenderFreezeTime(slowTime);
    }
    if (fabs(slowTime) < EPS) {
        slowTime = RESET_VALUE;
        duckSpeed = min(duckSpeed * 2.0f, DUCK_SPEED_LIMIT);
        wingSpeed = min(wingSpeed * 2.0f, WING_SPEED_LIMIT);
    }
}
void Tema1::NewDucks() {
    Ammo = maxAmmo;
    for (int i = 0; i < ducksOnScreen; ++i) {
        RandomDuckEffect(i);
        int randomPositionX = 50 + rand() % (marginX - 100);
        // generez doar unghiuri intre 30 si 150 de grade
        angleTurn[i] = (30.0f + (rand() % 232)) / 100;
        posHeadX[i] = randomPositionX;
        posHeadY[i] = dirtHeight + grassHeight;
        timeDuck = 2.11f;
        flyAway = false;
    }
}
void Tema1::DuckMovement(float deltaTimeSeconds, int i) {
    posHeadX[i] += duckSpeed * cos(angleTurn[i]) * deltaTimeSeconds;
    posHeadY[i] += duckSpeed * sin(angleTurn[i]) * deltaTimeSeconds;
}
void Tema1::AngleAdjustment(int i) {
    if (angleTurn[i] < 0)
        angleTurn[i] = 2 * PI + angleTurn[i];
    if (angleTurn[i] > 2 * PI)
        angleTurn[i] -= (2 * PI);
}
void Tema1::BossFightHealthBar() {

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(posXBossBar, posYBossBar);
    modelMatrix *= transform2D::Scale(bossBarScaling, 0.5);
    RenderMesh2D(meshes["wireframe"], modelMatrix, WHITE);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(posXBossBar, posYBossBar + barHeight / 2);
    modelMatrix *= transform2D::Scale(max(0,bigDuckHP * scalingFactor), 0.25);
    RenderMesh2D(meshes["loadingScore"], modelMatrix, RED);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(posXBossBar, posYBossBar);
    modelMatrix *= transform2D::Scale(max(0, bigDuckHP * scalingFactor), 0.25);
    RenderMesh2D(meshes["loadingScore"], modelMatrix, CRIMSON);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(posXBossBar + bossBarScaling * wireframeLength, posYBossBar);
    modelMatrix *= transform2D::Rotate(PI);
    modelMatrix *= transform2D::Translate(0, -barHeight);
    modelMatrix *= transform2D::Scale(min(BOSS_MAX_HP, (BOSS_MAX_HP - bigDuckHP)) * scalingFactor, 0.5);
    RenderMesh2D(meshes["loadingScore"], modelMatrix, BLACK);
}
void Tema1::Update(float deltaTimeSeconds)
{
    if (isStarting) {
        startingWindow();
        return;
    }
    if (flashTime <= 0)
        colorBackground = DARK_BLUE;
    else
        flashTime -= deltaTimeSeconds;
    glm::ivec2 resolution = window->GetResolution();
    timeDuck += deltaTimeSeconds;
    slowTime -= deltaTimeSeconds;
    changeDirection += deltaTimeSeconds;
    SlowTimeEffect();
    if (nrOfDucks > 5) {
        NewColorLevel();
        nrOfDucks = nrOfDucks % 5;
    }
    
    CheckKillingSpree(timeDuck);
    RenderBackground();
    if (numberOfLifes <= 0 || ducksOnScreen == 5) {
        return;
    }
    RenderInfo();
    RandomMovement(deltaTimeSeconds);
    if (fabs(timeDuck - 2.0f) < EPS) {
        NewDucks();
        bigDuckHP = BOSS_MAX_HP;
    }
    if (BIG_DUCK) {
        BossFightHealthBar();
    }
    if (BIG_DUCK && bigDuckHP <= 0) {
        deadDuck[0] = true;
    }
    for (int i = 0; i < ducksOnScreen; ++i) {
        if (timeDuck > 2.0f && !flyAway && !deadDuck[i]) {
            DuckMovement(deltaTimeSeconds, i);
            AngleAdjustment(i);
            CheckMargins(timeDuck);
            DuckAnimation(deltaTimeSeconds);
        }
        if (deadDuck[i]) {
            angleTurn[i] = 3 * PI / 2;
            DuckMovement(deltaTimeSeconds, i);
            DuckAnimation(deltaTimeSeconds);
        }
    }
    
    for (int i = 0; i < ducksOnScreen; ++i) {
        if ((timeDuck > timeOnScreen || Ammo == 0) && !deadDuck[i]) {
            killingSpree = 0;
            flyAway = true;
            angleTurn[i] = PI / 2;
            DuckMovement(deltaTimeSeconds, i);
            DuckAnimation(deltaTimeSeconds);
        }
        if (flyAway && posHeadY[i] > marginY + 200) {
            Ammo = 3;
            numberOfLifes--;
            timeDuck = 0;
            flyAway = false;
            lastBounce = RESET_VALUE;
            ResetVariables();
        }
    }
    if (CheckAllDucks()) {
        Ammo = maxAmmo;
        timeDuck = 0;
        lastBounce = RESET_VALUE;
        ResetVariables();
    }
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    glm::ivec2 resolution = window->GetResolution();
    posXCursor = (double) mouseX / (resolution.x / marginX);
    posYCursor = (double) (marginY - mouseY / (resolution.y / marginY));

    //modelMatrix = glm::mat3(1);
    //modelMatrix *= transform2D::Translate(marginX / 2 - 452 / 2, marginY - i * marginY / NUMBER_OF_BUTTONS - 50);
    //// 151 * 3 ; 25 * 3; 
    //modelMatrix *= transform2D::Scale(3, 3);
    //RenderMesh2D(meshes["button"], modelMatrix, colorButton[i]);

    for (int i = 0; i < NUMBER_OF_BUTTONS; ++i) {
        if (isStarting && posXCursor > (marginX / 2 - 226) && posXCursor < (marginX / 2 - 226) + 453 &&
            posYCursor < (marginY - i * marginY / NUMBER_OF_BUTTONS - 50) && posYCursor > (marginY - i * marginY / NUMBER_OF_BUTTONS - 125))
            colorButton[i] = GREEN;
        else
            colorButton[i] = LIME;
    }
}
void Tema1::checkButtonType() {
    if (colorButton[0] == GREEN) {
        isStarting = false;
    }
}
void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    for (int i = 0; i < NUMBER_OF_BUTTONS; ++i) {
        if (colorButton[i] == GREEN)
            checkButtonType();
    }
    if (Ammo <= 0)
        return;
    Ammo--;
    for (int i = 0; i < ducksOnScreen; ++i) {
        if ((posXCursor > posHeadX[i] - circleRadius && posXCursor < posHeadX[i] + circleRadius &&
            posYCursor > posHeadY[i] - circleRadius && posYCursor < posHeadY[i] + circleRadius)) {
            colorBackground = CRIMSON;
            flashTime = FLASH_TIME_LIMIT;
            if (BIG_DUCK) {
                bigDuckHP = bigDuckHP - BOSS_HEADSHOT_DAMAGE;
            }
            else {
                deadDuck[i] = true;
            }
            return;
        }   
        if (((posXCursor >= posHeadX[i] - triangleSide / 2 - (2 * triangleSide) * cos(angleTurn[i]) && posXCursor <= posHeadX[i]) ||
            (posXCursor <= posHeadX[i] + triangleSide / 2 - (2 * triangleSide) * cos(angleTurn[i]) && posXCursor >= posHeadX[i])) &&
            ((posYCursor >= posHeadY[i] - triangleSide / 2 - (2 * triangleSide) * sin(angleTurn[i]) && posYCursor <= posHeadY[i]) ||
            (posYCursor <= posHeadY[i] + triangleSide / 2 - (2 * triangleSide) * sin(angleTurn[i]) && posYCursor >= posHeadY[i]))) {
            colorBackground = CRIMSON;
            flashTime = FLASH_TIME_LIMIT;
            if (BIG_DUCK) {
                bigDuckHP = bigDuckHP - BOSS_BODYSHOT_DAMAGE;
            }
            else {
                deadDuck[i] = true;
            } 
            return;
        }
    }
    //flashTime = FLASH_TIME_LIMIT;
    //colorBackground = WHITE;
}
    

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
