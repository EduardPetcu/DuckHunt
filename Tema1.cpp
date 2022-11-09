#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;

const glm::vec3 CYAN = glm::vec3(0, 1, 1);
const glm::vec3 RED = glm::vec3(1, 0, 0);
const glm::vec3 YELLOW = glm::vec3(1, 1, 0);
const glm::vec3 LIME = glm::vec3(0.5f, 1, 0);
const glm::vec3 BROWN = glm::vec3(0.54f, 0.269f, 0.074f);
const glm::vec3 GREEN = glm::vec3(0, 0.5f, 0);
const glm::vec3 DIRT = glm::vec3(0.43f, 0.30f, 0.21f);
const glm::vec3 WHITE = glm::vec3(1, 1, 1);
const glm::vec3 LIGHT_GREEN = glm::vec3(0.53f, 0.60f, 0.335f);
const glm::vec3 ORANGE = glm::vec3(1, 0.5f, 0.312f);
const glm::vec3 ORCHID = glm::vec3(0.85f, 0.43f, 0.83f);
const glm::vec3 BLUE = glm::vec3(0, 0, 1);
const glm::vec3 BLACK = glm::vec3(0, 0, 0);
const glm::vec3 PURPLE = glm::vec3(0.86f, 0.41f, 0.97f);
const glm::vec3 LIGHT_BLUE = glm::vec3(0, 0.56f, 0.91f);

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */
bool ok = false;

Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0.34f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::CreateMeshes() {

    glm::vec3 corner = glm::vec3(0, 0, 0);

    Mesh* triangle1 = object2D::CreateTriangle("triangle1", corner, triangleSide, BROWN, true);
    AddMeshToList(triangle1);

    Mesh* triangle2 = object2D::CreateTriangle("triangle2", corner, triangleSide / 3, BROWN, true);
    AddMeshToList(triangle2);

    Mesh* triangle4 = object2D::CreateTriangle("triangle4", corner, triangleSide / 7, YELLOW, true);
    AddMeshToList(triangle4);

    Mesh* circle1 = object2D::CreateCircle("circle1", corner, circleRadius, GREEN, true);
    AddMeshToList(circle1);

    Mesh* dirt = object2D::CreateRectangle("dirt", corner, 2000, dirtHeight, DIRT, true);
    AddMeshToList(dirt);

    Mesh* grass = object2D::CreateRectangle("grass", corner, 2000, grassHeight, LIGHT_GREEN, true);
    AddMeshToList(grass);

    Mesh* target = object2D::CreateCircle("target", corner, circleRadius / 3, LIME, false);
    AddMeshToList(target);

    Mesh* targetCross = object2D::CreateCross("targetCross", corner, circleRadius / 3, RED);
    AddMeshToList(targetCross);

    Mesh* ammo = object2D::CreateRectangle("ammo", corner, 15, 25, GREEN, true);
    AddMeshToList(ammo);

    Mesh* wireframe = object2D::CreateRectangle("wireframe", corner, 206, 50, WHITE);
    AddMeshToList(wireframe);

    Mesh* loadingScore = object2D::CreateRectangle("loadingScore", corner, 5, 49, ORANGE, true);
    AddMeshToList(loadingScore);

    Mesh* bar = object2D::CreateBar("bar", corner, 151, 25, WHITE);
    AddMeshToList(bar);

    Mesh* diamond = object2D::CreateDiamond("diamond", corner, diamondLength1, diamondLength2, CYAN, LIGHT_BLUE, BLUE, true);
    AddMeshToList(diamond);
}
void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
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
    modelMatrix *= transform2D::Translate(0, 75);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(marginX - 350, marginY - 150);
    RenderMesh2D(meshes["wireframe"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(marginX - 349.5, marginY - 149.5);
    modelMatrix *= transform2D::Scale(1 + 4 * nrOfDucks, 1);
    RenderMesh2D(meshes["loadingScore"], modelMatrix, colorLevel);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(50, marginY - 101);
    RenderMesh2D(meshes["bar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(50, marginY - 151);
    RenderMesh2D(meshes["bar"], shaders["VertexColor"], modelMatrix);

}
void Tema1::WingAnimation(float deltaTimeSeconds) {
    if (rotationWings >= 0.4f) {
        changeWingDirection = true;
    }
    if (rotationWings <= -0.4f) {
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
        RenderMesh2D(meshes["circle1"], shaders["VertexColor"], modelMatrix);

        // corpu la rata
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(posHeadX[i] - circleRadius * cos(angleTurn[i]) - 2 * triangleSide,
            posHeadY[i] - circleRadius * sin(angleTurn[i]) - triangleSide / 2);
        modelMatrix *= transform2D::Translate(edgeBodyX, edgeBodyY);
        modelMatrix *= transform2D::Rotate(angleTurn[i]);
        modelMatrix *= transform2D::Translate(-edgeBodyX, -edgeBodyY);

        RenderMesh2D(meshes["triangle1"], modelMatrix, color[i]);

        WingAnimation(deltaTimeSeconds);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(posHeadX[i] - (circleRadius + triangleSide - triangleSide / 6) * cos(angleTurn[i]),
            posHeadY[i] - (circleRadius + triangleSide - triangleSide / 6) * sin(angleTurn[i]));
        modelMatrix *= transform2D::Rotate(1.57f + angleTurn[i]);
        modelMatrix *= transform2D::Translate(cx, cy);
        modelMatrix *= transform2D::Rotate(rotationWings);
        modelMatrix *= transform2D::Translate(-cx, -cy);

        RenderMesh2D(meshes["triangle2"], modelMatrix, color[i]);

        // aripa la rata
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(posHeadX[i] - (circleRadius + triangleSide + triangleSide / 6) * cos(angleTurn[i]),
            posHeadY[i] - (circleRadius + triangleSide + triangleSide / 6) * sin(angleTurn[i]));
        modelMatrix *= transform2D::Rotate(-1.57f + angleTurn[i]);
        modelMatrix *= transform2D::Translate(cx, cy);
        modelMatrix *= transform2D::Rotate(-rotationWings);
        modelMatrix *= transform2D::Translate(-cx, -cy);
        RenderMesh2D(meshes["triangle2"], modelMatrix, color[i]);

        // ciocu la rata
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(posHeadX[i] + circleRadius * cos(angleTurn[i]), posHeadY[i] +
                        circleRadius * sin(angleTurn[i]));
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
            angleTurn[i] = 6.28f - angleTurn[i];
            lastBounce = timeD;
        }
    }
}
void Tema1::CheckMargins(float timeD) {

    if (timeD - lastBounce < 0.1f)
        return;
    if (!flyAway) {
        CheckUpperMargin(timeD);
    }
    // MARGINE DREAPTA
    for (int i = 0; i < ducksOnScreen; ++i) {
        if (posHeadX[i] + circleRadius > marginX) {
            angleTurn[i] = 3.14f - angleTurn[i];
            lastBounce = timeD;
        }
    }
    // MARGINE STANGA
    for (int i = 0; i < ducksOnScreen; ++i) {
        if (posHeadX[i] < 0) {
            angleTurn[i] += 2 * (4.71f - angleTurn[i]);
            lastBounce = timeD;
        }
    }
    // MARGINE JOS
    for (int i = 0; i < ducksOnScreen; ++i) {
        if (posHeadY[i] - circleRadius < 0) {
            angleTurn[i] = 6.28f - angleTurn[i];
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
    // LEVEL 7
    if (colorLevel == BLUE) {
        ducksOnScreen++;
        colorLevel = LIME;
        return;
    }
}
void Tema1::RenderFreezeTime(float timeRemaining) {
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(marginX - 350, marginY - 230);
    RenderMesh2D(meshes["wireframe"], modelMatrix, WHITE);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(marginX - 349.5, marginY - 229.5);
    modelMatrix *= transform2D::Scale(timeRemaining * 2, 1);
    RenderMesh2D(meshes["loadingScore"], modelMatrix, ORCHID);
}
void Tema1::RandomDuckEffect(int i) {
    int randomDuck = rand() % 20;
    if (randomDuck <= 16) {
        color[i] = BROWN;
    }
    if (randomDuck == 17) {
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
        maxAmmo = min(maxAmmo + 1, 8);
    }
    if (color[i] == RED) {
        numberOfLifes = min(numberOfLifes + 1, 5);
    }
    if (color[i] == CYAN) {
        freezeTime = true;
        if (slowTime <= 0.0f) {
            duckSpeed = duckSpeed / 2;
            wingSpeed = wingSpeed / 2;
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
    for (int i = 0; i < ducksOnScreen; ++i) {
        if (deadDuck[i]) {
            duckCounter++;
            nrOfDucks++;
            killingSpree++;
            CheckBonusEffects(i);
        }
        deadDuck[i] = false;
        if (duckCounter % 5 == 0) {
            duckSpeed += duckSpeed / 5;
            wingSpeed += wingSpeed / 5;
        }
        nrOfDucks += killingSpree / 5;
    }
}
void Tema1::RandomMovement(float deltaTimeSeconds) {
    for (int i = 0; i < ducksOnScreen; ++i) {
         angleTurn[i] += 0.4 * randomAngle * deltaTimeSeconds;
    }
    if (fabs(changeDirection - 2.0f) < 0.1f) {
        for (int i = 0; i < ducksOnScreen; ++i) {
            randomAngle = (rand() % 2) * 2 - 1; // (generez -1 sau 1)
        }
        changeDirection = 0;
    }
}
void Tema1::SlowTimeEffect() {
    if (slowTime > 0.0f) {
        RenderFreezeTime(slowTime);
    }
    if (fabs(slowTime - 0.1f) < 0.1f) {
        slowTime = -1.0f;
        duckSpeed = duckSpeed * 2;
        wingSpeed = wingSpeed * 2;
    }
}
void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();
    timeDuck += deltaTimeSeconds;
    slowTime -= deltaTimeSeconds;
    changeDirection += deltaTimeSeconds;
    SlowTimeEffect();
    if (nrOfDucks > 10) {
        NewColorLevel();
        nrOfDucks = nrOfDucks % 10;
    }
    CheckKillingSpree(timeDuck);
    RenderInfo();
    RenderBackground();
    RandomMovement(deltaTimeSeconds);
    if (fabs(timeDuck - 2.0f) < 0.1) {
        Ammo = maxAmmo;
        for (int i = 0; i < ducksOnScreen; ++i) {
            RandomDuckEffect(i);
            int randomPositionX = 50 +  rand() % (marginX - 100);
            // generez doar unghiuri intre 30 si 150 de grade
            angleTurn[i] = (30.0f + (rand() % 232)) / 100;
            posHeadX[i] = randomPositionX;
            posHeadY[i] = dirtHeight + grassHeight;
            timeDuck = 2.11f;
            flyAway = false;
        }
    }
    for (int i = 0; i < ducksOnScreen; ++i) {
        if (timeDuck > 2.0f && !flyAway && !deadDuck[i]) {
            posHeadX[i] += duckSpeed * cos(angleTurn[i]) * deltaTimeSeconds;
            posHeadY[i] += duckSpeed * sin(angleTurn[i]) * deltaTimeSeconds;
            if (angleTurn[i] < 0)
                angleTurn[i] = 6.28f + angleTurn[i];
            if (angleTurn[i] > 6.28f)
                angleTurn[i] -= 6.28f;
            CheckMargins(timeDuck);
            DuckAnimation(deltaTimeSeconds);
        }
        if (deadDuck[i]) {
            angleTurn[i] = 4.71f;
            posHeadX[i] += duckSpeed * cos(angleTurn[i]) * deltaTimeSeconds;
            posHeadY[i] += duckSpeed * sin(angleTurn[i]) * deltaTimeSeconds;
            DuckAnimation(deltaTimeSeconds);
        }
    }
    
    for (int i = 0; i < ducksOnScreen; ++i) {
        if ((timeDuck > 8.0f || Ammo == 0) && !deadDuck[i]) {
            killingSpree = 0;
            flyAway = true;
            angleTurn[i] = 1.57f;
            posHeadX[i] += duckSpeed * cos(angleTurn[i]) * deltaTimeSeconds;
            posHeadY[i] += duckSpeed * sin(angleTurn[i]) * deltaTimeSeconds;
            DuckAnimation(deltaTimeSeconds);
        }
        if (flyAway && posHeadY[i] > marginY + 200) {
            Ammo = 3;
            numberOfLifes--;
            timeDuck = 0;
            flyAway = false;
            lastBounce = -1.0f;
            ResetVariables();
        }
    }
    if (CheckAllDucks()) {
        Ammo = maxAmmo;
        timeDuck = 0;
        lastBounce = -1.0f;
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
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (Ammo <= 0)
        return;
    Ammo--;
    for (int i = 0; i < ducksOnScreen; ++i) {
        if ((posXCursor > posHeadX[i] - circleRadius && posXCursor < posHeadX[i] + circleRadius &&
            posYCursor > posHeadY[i] - circleRadius && posYCursor < posHeadY[i] + circleRadius)) {
            deadDuck[i] = true;
            break;
        }
        if (((posXCursor > posHeadX[i] - (circleRadius + 2 * triangleSide) * cos(angleTurn[i]) && posXCursor < posHeadX[i]) ||
            (posXCursor < posHeadX[i] - (circleRadius + 2 * triangleSide) * cos(angleTurn[i]) && posXCursor > posHeadX[i])) &&
            ((posYCursor > posHeadY[i] - (circleRadius + 2 * triangleSide) * sin(angleTurn[i]) && posYCursor < posHeadY[i]) ||
                (posYCursor < posHeadY[i] - (circleRadius + 2 * triangleSide) * sin(angleTurn[i]) && posYCursor > posHeadY[i]))) {
            deadDuck[i] = true;
            break;
        }
    }
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
