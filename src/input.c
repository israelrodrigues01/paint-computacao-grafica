#include <stdio.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "paint.h"
#include "file.h"
#include "selection.h"
#include "globals.h"
#include "transformacoes.h"
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

static void updateSquarePoints(Point start, Point end)
{
    float dx = end.x - start.x;
    float dy = end.y - start.y;
    float side = fabsf(dx) < fabsf(dy) ? fabsf(dx) : fabsf(dy);

    float x2 = start.x + (dx < 0 ? -side : side);
    float y2 = start.y + (dy < 0 ? -side : side);

    squarePoints[0] = start;
    squarePoints[1].x = x2;
    squarePoints[1].y = start.y;
    squarePoints[2].x = x2;
    squarePoints[2].y = y2;
    squarePoints[3].x = start.x;
    squarePoints[3].y = y2;
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    // ---------------------------------------------------
    // TRANSFORMAÇÕES GEOMÉTRICAS — aplicadas no shape SELECIONADO
    // (antes elas atuavam sempre no último shape criado;
    // agora usam a seleção que o grupo já tinha implementado)
    // ---------------------------------------------------
    case 'r':
    case 'R': // Rotação +5 graus
        if (selectedShape >= 0 && selectedShape < totalShapes)
        {
            rotacao(&shapes[selectedShape], 5.0f);
            glutPostRedisplay();
        }
        break;

    case 'e':
    case 'E': // Rotação -5 graus
        if (selectedShape >= 0 && selectedShape < totalShapes)
        {
            rotacao(&shapes[selectedShape], -5.0f);
            glutPostRedisplay();
        }
        break;

    case 'a':
    case 'A': // Escala aumentar
        if (selectedShape >= 0 && selectedShape < totalShapes)
        {
            escala(&shapes[selectedShape], 1.1f, 1.1f);
            glutPostRedisplay();
        }
        break;

    case 'd':
    case 'D': // Escala diminuir (era 's'/'S', trocado para não conflitar com salvar)
        if (selectedShape >= 0 && selectedShape < totalShapes)
        {
            escala(&shapes[selectedShape], 0.9f, 0.9f);
            glutPostRedisplay();
        }
        break;

    case '0': // Reflexão eixo X
        if (selectedShape >= 0 && selectedShape < totalShapes)
        {
            reflexao(&shapes[selectedShape], 1.0f, -1.0f);
            glutPostRedisplay();
        }
        break;

    case '1': // Reflexão eixo Y
        if (selectedShape >= 0 && selectedShape < totalShapes)
        {
            reflexao(&shapes[selectedShape], -1.0f, 1.0f);
            glutPostRedisplay();
        }
        break;

    case '2': // Cisalhamento X +
        if (selectedShape >= 0 && selectedShape < totalShapes)
        {
            cisalhamento(&shapes[selectedShape], 0.1f, 0.0f);
            glutPostRedisplay();
        }
        break;

    case '3': // Cisalhamento X -
        if (selectedShape >= 0 && selectedShape < totalShapes)
        {
            cisalhamento(&shapes[selectedShape], -0.1f, 0.0f);
            glutPostRedisplay();
        }
        break;

    case '4': // Cisalhamento Y +
        if (selectedShape >= 0 && selectedShape < totalShapes)
        {
            cisalhamento(&shapes[selectedShape], 0.0f, 0.1f);
            glutPostRedisplay();
        }
        break;

    case '5': // Cisalhamento Y -
        if (selectedShape >= 0 && selectedShape < totalShapes)
        {
            cisalhamento(&shapes[selectedShape], 0.0f, -0.1f);
            glutPostRedisplay();
        }
        break;

    case '6': // Translação direita
        if (selectedShape >= 0 && selectedShape < totalShapes)
        {
            translacao(&shapes[selectedShape], 0.1f, 0.0f);
            glutPostRedisplay();
        }
        break;

    case '7': // Translação esquerda
        if (selectedShape >= 0 && selectedShape < totalShapes)
        {
            translacao(&shapes[selectedShape], -0.1f, 0.0f);
            glutPostRedisplay();
        }
        break;

    case '8': // Translação cima
        if (selectedShape >= 0 && selectedShape < totalShapes)
        {
            translacao(&shapes[selectedShape], 0.0f, 0.1f);
            glutPostRedisplay();
        }
        break;

    case '9': // Translação baixo
        if (selectedShape >= 0 && selectedShape < totalShapes)
        {
            translacao(&shapes[selectedShape], 0.0f, -0.1f);
            glutPostRedisplay();
        }
        break;

    // ---------------------------------------------------
    // FERRAMENTAS
    // ---------------------------------------------------
    case 'p':
        currentTool = TOOL_POINT;
        printf("Ferramenta: PONTO\n");
        break;

    case 'l':
        currentTool = TOOL_LINE;
        printf("Ferramenta: LINHA\n");
        break;

    case 'q':
        currentTool = TOOL_SQUARE;
        printf("Ferramenta: QUADRADO\n");
        break;

    case 'g':
        currentTool = TOOL_POLYGON;
        printf("Ferramenta: POLIGONO\n");
        break;

    case 'w': // Salvar (era 's', trocado para não conflitar com escala diminuir)
        saveDrawing();
        break;

    case 'c':
        loadDrawing();
        currentTool = TOOL_SELECTION;
        printf("Ferramenta: SELEÇÃO\n");
        break;

    case 'x':
        currentTool = TOOL_SELECTION;
        printf("Ferramenta: SELEÇÃO\n");
        break;

    case 127: // DELETE
    case 8:
        if (selectedShape >= 0 && selectedShape < totalShapes)
        {
            for (int i = selectedShape; i < totalShapes - 1; i++)
            {
                shapes[i] = shapes[i + 1];
            }
            totalShapes--;
            selectedShape = -1;
            glutPostRedisplay();
            printf("Shape deletado\n");
        }
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

            garantirEspacoNoVetor();
            calcularCentroide(&polygon);
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
    float mx = normalizeX(x);
    float my = normalizeY(y);

    mouseAtualX = x;
    mouseAtualY = y; //animação

    // Arrasta o shape selecionado (translação por drag-and-drop)
    if (currentTool == TOOL_SELECTION && draggingShape && selectedShape >= 0)
    {
        Shape *s = &shapes[selectedShape];
        float dx = mx - dragOffset.x;
        float dy = my - dragOffset.y;

        for (int i = 0; i < s->totalPoints; i++)
        {
            s->points[i].x += dx;
            s->points[i].y += dy;
        }

        s->centroide.x += dx;
        s->centroide.y += dy;

        dragOffset.x = mx;
        dragOffset.y = my;

        glutPostRedisplay();
        return;
    }

    if (drawingLine)
    {
        lineEnd.x = mx;
        lineEnd.y = my;

        glutPostRedisplay();
    }

    if (drawingSquare)
    {
        squareEnd.x = mx;
        squareEnd.y = my;

        updateSquarePoints(squareStart, squareEnd);

        glutPostRedisplay();
    }
}

void mouse(int button, int state, int x, int y)
{
    //animação:
    if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            mouseAtualX = x;
            mouseAtualY = y;
            ativarIma();
        }
        else
        {
            soltarIma();
        }
        return;
    }//

    if (button != GLUT_LEFT_BUTTON)
        return;

    float mx = normalizeX(x);
    float my = normalizeY(y);

    // SELEÇÃO DE SHAPE (ARRASTAR E SOLTAR)
    if (currentTool == TOOL_SELECTION)
    {
        if (state == GLUT_DOWN)
        {
            int idx = pickShape(shapes, totalShapes, mx, my);
            selectedShape = idx;

            if (idx >= 0)
            {
                draggingShape = 1;
                dragOffset.x = mx;
                dragOffset.y = my;
                printf("Shape %d selecionado\n", idx);
            }
            else
            {
                printf("Nenhum shape atingido\n");
            }
            glutPostRedisplay();
        }

        if (state == GLUT_UP)
        {
            draggingShape = 0;
        }

        return;
    }

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

            point.points[0].x = mx;
            point.points[0].y = my;
            point.points[0].h = 1.0f;

            garantirEspacoNoVetor();
            calcularCentroide(&point);
            shapes[totalShapes++] = point;

            glutPostRedisplay();
        }
    }

    if (currentTool == TOOL_LINE)
    {
        if (state == GLUT_DOWN)
        {
            drawingLine = 1;

            lineStart.x = mx;
            lineStart.y = my;
            lineStart.h = 1.0f;

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

            garantirEspacoNoVetor();
            calcularCentroide(&line);
            shapes[totalShapes++] = line;

            glutPostRedisplay();
        }
    }

    if (currentTool == TOOL_SQUARE)
    {
        if (state == GLUT_DOWN)
        {
            drawingSquare = 1;

            squareStart.x = mx;
            squareStart.y = my;

            squareEnd = squareStart;

            updateSquarePoints(squareStart, squareEnd);
        }

        if (state == GLUT_UP)
        {
            drawingSquare = 0;

            Shape square;

            square.tool = TOOL_SQUARE;

            square.color.r = 0;
            square.color.g = 0;
            square.color.b = 0;

            square.totalPoints = 4;

            for (int i = 0; i < 4; i++)
            {
                square.points[i] = squarePoints[i];
                square.points[i].h = 1.0f;
            }

            garantirEspacoNoVetor();
            calcularCentroide(&square);
            shapes[totalShapes++] = square;

            glutPostRedisplay();
        }
    }

    if (currentTool == TOOL_POLYGON)
    {
        if (state == GLUT_DOWN)
        {
            polygonPoints[polygonPointCount].x = mx;
            polygonPoints[polygonPointCount].y = my;
            polygonPoints[polygonPointCount].h = 1.0f;

            polygonPointCount++;

            drawingPolygon = 1;

            glutPostRedisplay();
        }
    }
}
