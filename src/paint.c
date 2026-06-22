#include <stdlib.h>
#include <stdio.h>
#include "paint.h"
#include "globals.h"
#include "transformacoes.h"

Shape *shapes = NULL;
int totalShapes = 0;
int capacidadeShapes = 0;

//animação:
int modoImaAtivo = 0;
int mouseAtualX = 0;
int mouseAtualY = 0; //

Tool currentTool = TOOL_POINT;

Point lineStart;
Point lineEnd;
int drawingLine = 0;

Point squareStart;
Point squareEnd;
Point squarePoints[4];
int drawingSquare = 0;

Point polygonPoints[MAX_POINTS];
int polygonPointCount = 0;
int drawingPolygon = 0;

int selectedShape = -1;
int draggingShape = 0;
Point dragOffset;

void calcularCentroide(Shape *s)
{
    float somaX = 0.0f;
    float somaY = 0.0f;

    for (int i = 0; i < s->totalPoints; i++)
    {
        somaX += s->points[i].x;
        somaY += s->points[i].y;
    }

    s->centroide.x = somaX / s->totalPoints;
    s->centroide.y = somaY / s->totalPoints;
}

void garantirEspacoNoVetor()
{
    if (totalShapes >= capacidadeShapes)
    {
        if (capacidadeShapes == 0)
        {
            capacidadeShapes = 10;
        }
        else
        {
            capacidadeShapes *= 2;
        }

        shapes = (Shape *)realloc(shapes, capacidadeShapes * sizeof(Shape));

        if (shapes == NULL)
        {
            printf("Erro: Faltou memoria RAM para expandir\n");
            exit(1);
        }
    }
}

//animação:
void ativarIma()
{
    modoImaAtivo = 1;
    for(int i = 0; i < totalShapes; i++)
    {
        shapes[i].centroideOriginal = shapes[i].centroide;
    }
}//
//animação:
void atualizarIma(int mouseX, int mouseY)
{
    if (!modoImaAtivo) return;

    float targetX = normalizeX(mouseX);
    float targetY = normalizeY(mouseY);

    for (int i = 0; i < totalShapes; i++)
    {
        float dx = (targetX - shapes[i].centroide.x) * 0.05f;
        float dy = (targetY - shapes[i].centroide.y) * 0.05f;

        translacao(&shapes[i], dx, dy);

        shapes[i].centroide.x += dx;
        shapes[i].centroide.y += dy;
    }
}//
//animação:
void soltarIma()
{
    modoImaAtivo = 0;
    for(int i = 0; i < totalShapes; i++)
    {
        float dx = shapes[i].centroideOriginal.x - shapes[i].centroide.x;
        float dy = shapes[i].centroideOriginal.y - shapes[i].centroide.y;
        translacao(&shapes[i], dx, dy);
        shapes[i].centroide = shapes[i].centroideOriginal;
    }
}//
