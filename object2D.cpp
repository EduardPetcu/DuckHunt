#include "object2D.h"

#include <vector>
#include <iostream>
#include "core/engine.h"
#include "utils/gl_utils.h"



Mesh* object2D::CreateRectangle(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    float length2,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length2, 0), color),
        VertexFormat(corner + glm::vec3(0, length2, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    } else {
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D::CreateTriangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(0, length, 0), color),
        VertexFormat(corner + glm::vec3(2 * length,length / 2, 0), color),
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2};

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    }

    triangle->InitFromData(vertices, indices);
    return triangle;
}
Mesh* object2D::CreateCircle(
    const std::string& name,
    glm::vec3 center,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = center;
    std::vector<VertexFormat> vertices;
    vertices.push_back(VertexFormat(corner, color));
    for (int i = 0; i < 360; i++) {
        vertices.push_back(VertexFormat(corner + glm::vec3(length * sin(i * 0.017f), length * cos(i * 0.017f), 0), color));
    }
    
    Mesh* circle = new Mesh(name);
    std::vector<unsigned int> indices;
    for (int i = 1; i < 360; ++i) {
        if (fill) {
            indices.push_back(0);
            indices.push_back(i + 1);
        }
        indices.push_back(i);
    }
    if (fill) {
        indices.push_back(0);
        indices.push_back(1);
    }
    indices.push_back(360);
    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
    }

    circle->InitFromData(vertices, indices);
    return circle;
}

Mesh* object2D::CreateCross(
    const std::string& name,
    glm::vec3 center,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = center;
    std::vector<VertexFormat> vertices;
    vertices.push_back(VertexFormat(corner, color));
    for (int i = 0; i < 4; i++) {
        vertices.push_back(VertexFormat(corner + glm::vec3(length * sin(i * 1.57f), length * cos(i * 1.57f), 0), color));
    }

    Mesh* cross = new Mesh(name);
    std::vector<unsigned int> indices;
    for (int i = 1; i <= 4; ++i) {
        indices.push_back(0);
        indices.push_back(i);
    }
    if (!fill) {
        cross->SetDrawMode(GL_LINE_LOOP);
    }

    cross->InitFromData(vertices, indices);
    return cross;
}

Mesh* object2D::CreateBar(
    const std::string& name,
    glm::vec3 center,
    float length,
    float length2,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = center;
    std::vector<VertexFormat> vertices;
    vertices.push_back(VertexFormat(corner, color));
    vertices.push_back(VertexFormat(corner + glm::vec3(2, 2, 0), color));
    vertices.push_back(VertexFormat(corner + glm::vec3(2.0f + length, 2, 0), color));
    vertices.push_back(VertexFormat(corner + glm::vec3(4.0f + length, 0, 0), color));
    vertices.push_back(VertexFormat(corner + glm::vec3(4.0f + length, -length2, 0), color));
    vertices.push_back(VertexFormat(corner + glm::vec3(2.0f + length, -length2 - 2.0f, 0), color));
    vertices.push_back(VertexFormat(corner + glm::vec3(2.0f, -length2 - 2.0f, 0), color));
    vertices.push_back(VertexFormat(corner + glm::vec3(0, -length2, 0), color));

    Mesh* bar = new Mesh(name);
    std::vector<unsigned int> indices;
    
    if (!fill) {
        for (int i = 0; i < 8; ++i) {
            indices.push_back(i);
        }
        bar->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        int count = 0;
        for (int i = 0; i < 8; ++i) {
            indices.push_back(i);
            if (count % 3 == 2) {
                indices.push_back(i);
                count++;
            }   
            count++;
        }
        indices.push_back(0);
        for (int i = 0; i < 8; i += 2) {
            indices.push_back(i);
            if (i == 4) {
                indices.push_back(i);
            }
        }
        indices.push_back(0);
        //bar->SetDrawMode(GL_TRIANGLES);
    }

    bar->InitFromData(vertices, indices);
    return bar;
}

Mesh* object2D::CreateDiamond(
    const std::string& name,
    glm::vec3 center,
    float length,
    float length2,
    glm::vec3 color,
    glm::vec3 color2,
    glm::vec3 color3,
    bool fill)
{
    glm::vec3 corner = center;
    std::vector<VertexFormat> vertices;
    vertices.push_back(VertexFormat(corner, color)); // 0
    vertices.push_back(VertexFormat(corner + glm::vec3(length, length, 0), color)); // 1
    vertices.push_back(VertexFormat(corner + glm::vec3(length2, -length2, 0), color)); // 2

    vertices.push_back(VertexFormat(corner + glm::vec3(2 * length2 - length, length, 0), color2)); // 3
    vertices.push_back(VertexFormat(corner + glm::vec3(length, length, 0), color2)); // 4
    vertices.push_back(VertexFormat(corner + glm::vec3(length2, -length2, 0), color2)); // 5

    vertices.push_back(VertexFormat(corner + glm::vec3(2 * length2 - length, length, 0), color3)); // 6
    vertices.push_back(VertexFormat(corner + glm::vec3(2 * length2, 0, 0), color3)); // 7
    vertices.push_back(VertexFormat(corner + glm::vec3(length2, -length2, 0), color3)); // 8

    Mesh* diamond = new Mesh(name);
    std::vector<unsigned int> indices;
    if (!fill) {
        for (int i = 0; i <= 8; ++i) {
            indices.push_back(i);
        }
        diamond->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices = { 0, 1, 2,
                    3, 4, 5,
                    6, 7, 8 
                   };
    }
    diamond->InitFromData(vertices, indices);
    return diamond;
}
