#include "lab_m1/Tema1/Tema1.h"
#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"
#include "lab_m1/Tema1/Defines.h"

using namespace std;
using namespace m1;

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