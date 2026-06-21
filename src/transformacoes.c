#include <math.h>
#include "paint.h"
#include "transformacoes.h"
#define PI 3.14159265358979323846

Matriz3x3 multiplicarMatrizes(Matriz3x3 A, Matriz3x3 B)
{
    Matriz3x3 Res;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Res.m[i][j] = 0;
            for (int k = 0; k < 3; k++)
            {
                Res.m[i][j] += A.m[i][k] * B.m[k][j];
            }
        }
    }
    return Res;
}
Matriz3x3 criarMatrizTransladaIda(float xr, float yr)
{
    Matriz3x3 T_ida = {{
            {1.0f, 0.0f, -xr},
            {0.0f, 1.0f, -yr},
            {0.0f, 0.0f, 1.0f}
        }
    };
    return T_ida;
}

Matriz3x3 criarMatrizTransladaVolta(float xr, float yr)
{
    Matriz3x3 T_volta = {{
            {1.0f, 0.0f, xr},
            {0.0f, 1.0f, yr},
            {0.0f, 0.0f, 1.0f}
        }
    };
    return T_volta;
}

void aplicarTransformacao(Shape *shape, Matriz3x3 M)
{
    for (int i = 0; i < shape->totalPoints; i++)
    {
        Point P = shape->points[i];
        shape->points[i].x = M.m[0][0]*P.x + M.m[0][1]*P.y + M.m[0][2]*P.h;
        shape->points[i].y = M.m[1][0]*P.x + M.m[1][1]*P.y + M.m[1][2]*P.h;
        shape->points[i].h = M.m[2][0]*P.x + M.m[2][1]*P.y + M.m[2][2]*P.h;
    }
    calcularCentroide(shape);
}

void rotacao(Shape *shape, float angulo)
{
    float xr = shape->centroide.x;
    float yr = shape->centroide.y;
    float theta_rad = angulo * PI / 180.0f;
    float c = cos(theta_rad);
    float s = sin(theta_rad);

    Matriz3x3 T_ida = criarMatrizTransladaIda(xr, yr);
    Matriz3x3 T_volta = criarMatrizTransladaVolta(xr, yr);
    Matriz3x3 R = {{
            {c, -s, 0.0f},
            {s, c, 0.0f},
            {0.0f, 0.0f, 1.0f}
        }
    };

    Matriz3x3 Matriz_provisoria = multiplicarMatrizes(R, T_ida);
    Matriz3x3 M_composta = multiplicarMatrizes(T_volta, Matriz_provisoria);

    aplicarTransformacao(shape, M_composta);

}

void escala(Shape *shape, float sx, float sy)
{

    float xr = shape->centroide.x;
    float yr = shape->centroide.y;

    Matriz3x3 T_ida = criarMatrizTransladaIda(xr, yr);
    Matriz3x3 T_volta = criarMatrizTransladaVolta(xr, yr);

    Matriz3x3 S = {{
            {sx, 0.0f, 0.0f},
            {0.0f, sy, 0.0f},
            {0.0f, 0.0f, 1.0f}
        }
    };

    Matriz3x3 Matriz_provisoria = multiplicarMatrizes(S, T_ida);
    Matriz3x3 M_composta = multiplicarMatrizes(T_volta, Matriz_provisoria);

    aplicarTransformacao(shape, M_composta);

}

void reflexao(Shape *shape, float x, float y)
{

    float xr = shape->centroide.x;
    float yr = shape->centroide.y;

    Matriz3x3 T_ida = criarMatrizTransladaIda(xr, yr);
    Matriz3x3 T_volta = criarMatrizTransladaVolta(xr, yr);

    Matriz3x3 Re = {{
            {x, 0.0f, 0.0f},
            {0.0f, y, 0.0f},
            {0.0f, 0.0f, 1.0f}
        }
    };

    Matriz3x3 Matriz_provisoria = multiplicarMatrizes(Re, T_ida);
    Matriz3x3 M_composta = multiplicarMatrizes(T_volta, Matriz_provisoria);

    aplicarTransformacao(shape, M_composta);
}

void cisalhamento(Shape *shape, float shx, float shy)
{

    float xr = shape->centroide.x;
    float yr = shape->centroide.y;

    Matriz3x3 T_ida = criarMatrizTransladaIda(xr, yr);
    Matriz3x3 T_volta = criarMatrizTransladaVolta(xr, yr);

    Matriz3x3 C = {{
            {1.0f, shx, 0.0f},
            {shy, 1.0f, 0.0f},
            {0.0f, 0.0f, 1.0f}
        }
    };

    Matriz3x3 Matriz_provisoria = multiplicarMatrizes(C, T_ida);
    Matriz3x3 M_composta = multiplicarMatrizes(T_volta, Matriz_provisoria);

    aplicarTransformacao(shape, M_composta);
}

void translacao(Shape *shape, float tx, float ty)
{
    Matriz3x3 T = {{
            {1.0f, 0.0f, tx},
            {0.0f, 1.0f, ty},
            {0.0f, 0.0f, 1.0f}
        }
    };

    aplicarTransformacao(shape, T);
}




