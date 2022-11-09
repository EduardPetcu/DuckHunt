#pragma once

#include "components/simple_scene.h"
#define MAX_DUCKS 10

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
        void RenderFreezeTime(float timeRemaining);
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

     protected:
        float cx, cy;
        bool flyAway = false, freezeTime = false;
        bool deadDuck[MAX_DUCKS] = {false};
        glm::mat3 modelMatrix;
        glm::vec3 color[MAX_DUCKS], colorLevel;
        int marginX, marginY;
        float translateX, translateY;
        float scaleX, scaleY, bonusX, bonusY;
        float angleTurn[MAX_DUCKS];
        const float MOUSE_SPEED = 0.85f;
        double posXCursor = 250, posYCursor = 250, posZBox = 0;
        float diamondLength1 = 12.5, diamondLength2 = 25;
        float rotationWings = 0;
        bool changeWingDirection = false;
        float posHeadX[MAX_DUCKS], posHeadY[MAX_DUCKS];
        float triangleSide, circleRadius, grassHeight, dirtHeight;
        float timeDuck = 0, slowTime = 0 , lastBounce = 0, changeDirection = 0;
        float duckSpeed = 190.0f, wingSpeed = 2.8f, reducedSpeed = 50.0f;
        float edgeBodyX, edgeBodyY, edgeWingX, edgeWingY;
        int numberOfLifes, Ammo, nrOfDucks, maxAmmo, randomAngle;
        int score, killingSpree, scoreMultiplier, duckCounter, ducksOnScreen;
    };
}   // namespace m1
