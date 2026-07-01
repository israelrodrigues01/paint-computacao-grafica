#include "earclipping.h"
#include "paint.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static float produtoVetorial(Point A, Point B, Point C)
{
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}
 
static int pontoNoTriangulo(Point A, Point B, Point C, Point P)
{
    float d1 = produtoVetorial(A, B, P);
    float d2 = produtoVetorial(B, C, P);
    float d3 = produtoVetorial(C, A, P);
 
    int temNeg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    int temPos = (d1 > 0) || (d2 > 0) || (d3 > 0);
 
    return !(temNeg && temPos);
}
 
static int eAntiHorario(Point *pts, int n)
{
    float area = 0;
    for (int i = 0; i < n; i++)
    {
        int j = (i + 1) % n;
        area += pts[i].x * pts[j].y;
        area -= pts[j].x * pts[i].y;
    }
    return area > 0;
}

static void inverterOrdem(Point *pts, int n)
{
    for (int i = 0; i < n / 2; i++)
    {
        Point tmp = pts[i];
        pts[i] = pts[n - 1 - i];
        pts[n - 1 - i] = tmp;
    }
}

static void removerPonto(Point *pts, int *n, int idx)
{
    for (int i = idx; i < *n - 1; i++)
        pts[i] = pts[i + 1];
    (*n)--;
}

static int eOrelha(Point *pts, int n, int i)
{
    int prev = (i - 1 + n) % n;
    int next = (i + 1) % n;

    Point A = pts[prev];
    Point B = pts[i];
    Point C = pts[next];

    if (produtoVetorial(A, B, C) <= 0)
        return 0;

    for (int j = 0; j < n; j++)
    {
        if (j == prev || j == i || j == next)
            continue;

        if (pontoNoTriangulo(A, B, C, pts[j]))
            return 0;
    }

    return 1;
}

static float cx_global, cy_global;

static int compararAngulo(const void *a, const void *b)
{
    Point *pa = (Point *)a;
    Point *pb = (Point *)b;
    float angA = atan2f(pa->y - cy_global, pa->x - cx_global);
    float angB = atan2f(pb->y - cy_global, pb->x - cx_global);
    if (angA < angB) return -1;
    if (angA > angB) return  1;
    return 0;
}

void earClipping(Shape *s)
{
    if (s->tool != TOOL_POLYGON || s->totalPoints < 4)
    {
        printf("Ear Clipping: precisa de um poligono com pelo menos 4 vertices\n");
        return;
    }

    Point pts[MAX_POINTS];
    int n = s->totalPoints;
    for (int i = 0; i < n; i++)
        pts[i] = s->points[i];

    if (!eAntiHorario(pts, n))
        inverterOrdem(pts, n);

    Point hull[MAX_POINTS];
    int hullN = 0;

    int seguranca = n * n;
    while (n > 3 && seguranca-- > 0)
    {
        int encontrou = 0;
        for (int i = 0; i < n; i++)
        {
            if (eOrelha(pts, n, i))
            {
                removerPonto(pts, &n, i);
                encontrou = 1;
                break;
            }
        }

        if (!encontrou)
        {
            printf("Ear Clipping: nenhuma orelha encontrada, poligono pode ser degenerado\n");
            break;
        }
    }

    Point todos[MAX_POINTS];
    int totalTodos = s->totalPoints;
    for (int i = 0; i < totalTodos; i++)
        todos[i] = s->points[i];

    float somX = 0, somY = 0;
    for (int i = 0; i < totalTodos; i++)
    {
        somX += todos[i].x;
        somY += todos[i].y;
    }
    cx_global = somX / totalTodos;
    cy_global = somY / totalTodos;

    qsort(todos, totalTodos, sizeof(Point), compararAngulo);

    Point convexo[MAX_POINTS];
    int convexoN = 0;

    for (int i = 0; i < totalTodos; i++)
    {
        while (convexoN >= 2 &&
               produtoVetorial(convexo[convexoN - 2],
                               convexo[convexoN - 1],
                               todos[i]) <= 0)
        {
            convexoN--;
        }
        convexo[convexoN++] = todos[i];
    }

    int tamanhoFinal = convexoN;
    for (int i = 0; i < tamanhoFinal; i++)
    {
        while (convexoN >= 2 &&
               produtoVetorial(convexo[convexoN - 2],
                               convexo[convexoN - 1],
                               convexo[i]) <= 0)
        {
            convexoN--;
        }
    }

    s->totalPoints = convexoN;
    for (int i = 0; i < convexoN; i++)
        s->points[i] = convexo[i];

    calcularCentroide(s);

    printf("Ear Clipping: poligono transformado em convexo (%d vertices)\n", convexoN);
}
