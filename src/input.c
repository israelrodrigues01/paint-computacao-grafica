#include <stdio.h>
#include <GL/glut.h>
#include <stdio.h>
#include "paint.h"
#include "file.h"
#include "globals.h"
#include <string.h>
#include <stdlib.h>

float normalizeX(int x)
{
    return (2.0f * x / WINDOW_WIDTH) - 1.0f;
}

float normalizeY(int y)
{
    return 1.0f - (2.0f * y / WINDOW_HEIGHT);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'p':
        currentTool = TOOL_POINT;
        printf("Ferramenta: PONTO\n");
        break;

    case 'l':
        currentTool = TOOL_LINE;
        printf("Ferramenta: LINHA\n");
        break;

    case 'g':
        currentTool = TOOL_POLYGON;
        printf("Ferramenta: POLIGONO\n");
        break;

    case 's':
        saveDrawing();
        break;

    case 'c':
        loadDrawing();
        break;

    case 13: // ENTER

        if (currentTool == TOOL_POLYGON &&
            polygonPointCount >= 3)
        {
            Shape polygon;

            polygon.tool = TOOL_POLYGON;

            polygon.color.r = 0;
            polygon.color.g = 1;
            polygon.color.b = 0;

            polygon.totalPoints = polygonPointCount;

            for (int i = 0; i < polygonPointCount; i++)
            {
                polygon.points[i] = polygonPoints[i];
            }

            shapes[totalShapes++] = polygon;

            polygonPointCount = 0;

            drawingPolygon = 0;

            glutPostRedisplay();

            printf("Poligono criado\n");
        }
        break;

    case 27: // ESC

        saveDrawing();

        printf("Saindo...\n");

        exit(0);

        break;
    }
}

void mouseMotion(int x, int y)
{
    if (drawingLine)
    {
        lineEnd.x = normalizeX(x);
        lineEnd.y = normalizeY(y);

        glutPostRedisplay();
    }
}

void mouse(int button, int state, int x, int y)
{
    if (button != GLUT_LEFT_BUTTON)
        return;

    if (currentTool == TOOL_POINT)
    {
        if (state == GLUT_DOWN)
        {
            Shape point;

            point.tool = TOOL_POINT;

            point.color.r = 1;
            point.color.g = 0;
            point.color.b = 0;

            point.totalPoints = 1;

            point.points[0].x = normalizeX(x);
            point.points[0].y = normalizeY(y);

            shapes[totalShapes++] = point;

            glutPostRedisplay();
        }
    }

    if (currentTool == TOOL_LINE)
    {
        if (state == GLUT_DOWN)
        {
            drawingLine = 1;

            lineStart.x = normalizeX(x);
            lineStart.y = normalizeY(y);

            lineEnd = lineStart;
        }

        if (state == GLUT_UP)
        {
            drawingLine = 0;

            Shape line;

            line.tool = TOOL_LINE;

            line.color.r = 0;
            line.color.g = 0;
            line.color.b = 1;

            line.totalPoints = 2;

            line.points[0] = lineStart;
            line.points[1] = lineEnd;

            shapes[totalShapes++] = line;

            glutPostRedisplay();
        }
    }

    if (currentTool == TOOL_POLYGON)
    {
        if (state == GLUT_DOWN)
        {
            polygonPoints[polygonPointCount].x = normalizeX(x);
            polygonPoints[polygonPointCount].y = normalizeY(y);

            polygonPointCount++;

            drawingPolygon = 1;

            glutPostRedisplay();
        }
    }
}