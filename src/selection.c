#include "selection.h"
#include <stdio.h>
#include <math.h>

int pickPonto(float px, float py, float mx, float my, float t) {
  if (mx <= px + t && mx >= px - t) {
    if (my <= py + t && my >= py - t) {
      return 1;
    }
  }
  return 0;
}

#define ESQUERDA 8 // 1000
#define DIREITA 4  // 0100
#define ACIMA 2    // 0010
#define ABAIXO 1   // 0001

static int regionCode(float px, float py, float xmin, float xmax, float ymin, float ymax) {
  int code = 0;

  if (px < xmin) code |= ESQUERDA;
  if (px > xmax) code |= DIREITA;
  if (py < ymin) code |= ABAIXO;
  if (py > ymax) code |= ACIMA;

  return code;
}

static float clamp(float value, float min, float max)
{
  if (value < min)
    return min;
  if (value > max)
    return max;
  return value;
}

static int pointNearSegment(float px, float py, float x1, float y1, float x2, float y2, float tolerance)
{
  float dx = x2 - x1;
  float dy = y2 - y1;
  float lengthSquared = dx * dx + dy * dy;

  if (lengthSquared == 0.0f)
  {
    float distX = px - x1;
    float distY = py - y1;
    return (distX * distX + distY * distY) <= tolerance * tolerance;
  }

  float t = ((px - x1) * dx + (py - y1) * dy) / lengthSquared;
  t = clamp(t, 0.0f, 1.0f);

  float projX = x1 + t * dx;
  float projY = y1 + t * dy;
  float distX = px - projX;
  float distY = py - projY;

  return (distX * distX + distY * distY) <= tolerance * tolerance;
}

int pickLinha(float x0, float y0, float x1, float y1, float mx, float my, float t) {
  float xmin = mx - t;
  float xmax = mx + t;
  float ymin = my - t;
  float ymax = my + t;

  int code0 = regionCode(x0, y0, xmin, xmax, ymin, ymax);
  int code1 = regionCode(x1, y1, xmin, xmax, ymin, ymax);

  while (1) {
    if ((code0 | code1) == 0) {
      return 1; // Linha completamente dentro do retângulo
    }
    if (code0 & code1) {
      return 0; // Linha completamente fora do retângulo
    }

    int codeOut = code0 != 0 ? code0 : code1;
    float x, y;

    if (codeOut & ESQUERDA) {
      y = y0 + (xmin - x0) * (y1 - y0) / (x1 - x0);
      x = xmin;
    } else if (codeOut & DIREITA) {
      y = y0 + (xmax - x0) * (y1 - y0) / (x1 - x0);
      x = xmax;
    } else if (codeOut & ABAIXO) {
      x = x0 + (ymin - y0) * (x1 - x0) / (y1 - y0);
      y = ymin;
    } else {
      x = x0 + (ymax - y0) * (x1 - x0) / (y1 - y0);
      y = ymax;
    }

    if (codeOut == code0) {
      x0 = x;
      y0 = y;
      code0 = regionCode(x0, y0, xmin, xmax, ymin, ymax);
    } else {
      x1 = x;
      y1 = y;
      code1 = regionCode(x1, y1, xmin, xmax, ymin, ymax);
    }
  }
}

int pickArea(Point *points, int n, float mx, float my) {
  int intersections = 0;

  for (int i = 0; i < n; i++) {
    Point p1 = points[i];
    Point p2 = points[(i + 1) % n];

    if (pointNearSegment(mx, my, p1.x, p1.y, p2.x, p2.y, SELECTION_TOLERANCE)) {
      return 1;
    }
  }

  for (int i = 0; i < n; i++) {
    float p1x = points[i].x;
    float p1y = points[i].y;
    float p2x = points[(i + 1) % n].x;
    float p2y = points[(i + 1) % n].y;

    if (p1y == p2y && p1y == my)
      continue;

    if (p1y > my && p2y > my)
      continue;

    if (p1y < my && p2y < my)
      continue;

    if (p1x < mx && p2x < mx)
      continue;

    if ((p1x > mx && p2x > mx) && ((p1y > my && p2y < my) || (p1y < my && p2y > my))) {
      intersections++;
      continue;
    }

    if (!((p1y >= my && p2y < my) || (p1y < my && p2y >= my)))
      continue;

    float xi = p1x + (my - p1y) * (p2x - p1x) / (p2y - p1y);

    if (xi > mx)
      intersections++;
  }

  return (intersections % 2 == 1) ? 1 : 0;
}

int pickShape(Shape *shapes, int total, float mx, float my) {
  for (int i = total - 1; i >= 0; i--) {
    Shape *shape = &shapes[i];

    if (shape->tool == TOOL_POINT) {
      if (pickPonto(shape->points[0].x, shape->points[0].y, mx, my, SELECTION_TOLERANCE)) {
        return i;
      }
    } else if (shape->tool == TOOL_LINE) {
      if (pickLinha(shape->points[0].x, shape->points[0].y, shape->points[1].x, shape->points[1].y, mx, my, SELECTION_TOLERANCE)) {
        return i;
      }
    } else if (shape->tool == TOOL_POLYGON || shape->tool == TOOL_SQUARE) {
      if (pickArea(shape->points, shape->totalPoints, mx, my)) {
        return i;
      }
    }
  }
  return -1; // Nenhuma forma selecionada
}