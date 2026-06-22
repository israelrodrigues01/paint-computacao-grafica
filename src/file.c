#include <stdio.h>
#include <stdio.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "paint.h"
#include "globals.h"
#include <string.h>
#include <stdlib.h>


void saveDrawing()
{
    FILE *file = fopen("drawing.txt", "w");

    if (file == NULL)
    {
        printf("Erro ao salvar arquivo\n");
        return;
    }

    fprintf(file, "%d\n\n", totalShapes);

    for (int i = 0; i < totalShapes; i++)
    {
        Shape shape = shapes[i];

        switch (shape.tool)
        {
        case TOOL_POINT:
            fprintf(file, "POINT\n");
            break;

        case TOOL_LINE:
            fprintf(file, "LINE\n");
            break;

        case TOOL_SQUARE:
            fprintf(file, "SQUARE\n");
            break;

        case TOOL_POLYGON:
            fprintf(file, "POLYGON\n");
            break;

        case TOOL_SELECTION:
            break;
        }

        fprintf(
            file,
            "%f %f %f\n",
            shape.color.r,
            shape.color.g,
            shape.color.b);

        fprintf(
            file,
            "%d\n",
            shape.totalPoints);

        for (int j = 0; j < shape.totalPoints; j++)
        {
            fprintf(
                file,
                "%f %f\n",
                shape.points[j].x,
                shape.points[j].y);
        }

        fprintf(file, "\n");
    }

    fclose(file);

    printf("Desenho salvo!\n");
}

void loadDrawing()
{
    FILE *file = fopen("drawing.txt", "r");

    if (file == NULL)
    {
        printf("Nenhum desenho encontrado.\n");
        return;
    }

    totalShapes = 0;

    int quantidade;

    fscanf(file, "%d", &quantidade);

    for (int i = 0; i < quantidade; i++)
    {
        Shape shape;

        char tipo[20];

        fscanf(file, "%s", tipo);

        if (strcmp(tipo, "POINT") == 0)
            shape.tool = TOOL_POINT;

        else if (strcmp(tipo, "LINE") == 0)
            shape.tool = TOOL_LINE;

        else if (strcmp(tipo, "SQUARE") == 0)
            shape.tool = TOOL_SQUARE;

        else if (strcmp(tipo, "POLYGON") == 0)
            shape.tool = TOOL_POLYGON;

        fscanf(
            file,
            "%f %f %f",
            &shape.color.r,
            &shape.color.g,
            &shape.color.b);

        fscanf(
            file,
            "%d",
            &shape.totalPoints);

        for (int j = 0; j < shape.totalPoints; j++)
        {
            fscanf(
                file,
                "%f %f",
                &shape.points[j].x,
                &shape.points[j].y);

            shape.points[j].h = 1.0f;
        }

        calcularCentroide(&shape);
        shape.centroideOriginal = shape.centroide;

        garantirEspacoNoVetor();
        shapes[totalShapes++] = shape;
    }

    fclose(file);

    glutPostRedisplay();

    printf("Desenho carregado!\n");
}
