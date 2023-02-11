#pragma once

#include "components/simple_scene.h"
#define MAX_DUCKS 6
#define NUMBER_OF_BUTTONS 3
namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();
        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        
        void InitVariables();
        bool CheckAllDucks();
        void CreateMeshes();
        void RenderBackground();
        void RandomDuckEffect(int i);
        void CheckBonusEffects(int i);
        void NewColorLevel();
        void RenderInfo();
        void ResetVariables();
        void CheckKillingSpree(float time);
        bool RescaleDiamond(float time);
        void CheckMargins(float time);
        void CheckUpperMargin(float time);
        void SlowTimeEffect();
        void NewDucks();
        void BossFightHealthBar();
        void AngleAdjustment(int duckNumber);
        void RenderFreezeTime(float timeRemaining);
        void DuckMovement(float timeRemaining, int duckNumber);
        void DuckAnimation(float deltaTimeSeconds);
        void WingAnimation(float deltaTimeSeconds);
        void RandomMovement(float deltaTimeSeconds);
        void FlyAway(float deltaTimeSeconds);
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void startingWindow();
        void checkButtonType();
     protected:
        float cx, cy;
        bool flyAway = false, freezeTime = false, BIG_DUCK;
        bool deadDuck[MAX_DUCKS] = {false};
        glm::mat3 modelMatrix;
        glm::vec3 color[MAX_DUCKS], colorLevel, colorBackground, colorButton[NUMBER_OF_BUTTONS];
        int marginX, marginY;
        float translateX, translateY;
        float scaleX, scaleY, bonusX, bonusY;
        float angleTurn[MAX_DUCKS];
        const float MOUSE_SPEED = 0.85f;
        float posXCursor = 250, posYCursor = 250, posZBox = 0;
        float diamondLength1 = 12.5, diamondLength2 = 25;
        float rotationWings = 0;
        bool changeWingDirection = false;
        float posHeadX[MAX_DUCKS], posHeadY[MAX_DUCKS];
        float triangleSide, circleRadius, grassHeight, dirtHeight, barLength, barHeight, wireframeLength;
        float timeDuck = 0, slowTime = 0 , lastBounce = 0, changeDirection = 0, flashTime;
        float duckSpeed = 140, wingSpeed = 2.8f, reducedSpeed = 50.0f, wingTurnTime = 0.4f;
        int posXBossBar = 300, posYBossBar = 670;
        float edgeBodyX, edgeBodyY, edgeWingX, edgeWingY, timeOnScreen = 8.0f, bossBarScaling = 3.05f;
        int numberOfLifes, Ammo, nrOfDucks, maxAmmo, randomAngle, scalingFactor = 25;
        int score, killingSpree, scoreMultiplier, duckCounter, ducksOnScreen, bigDuckHP, ducksOnScreenCopy;
        bool isStarting = true;
    };
}   // namespace m1
