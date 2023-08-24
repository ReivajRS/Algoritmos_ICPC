const double INF = 1e9, EPS = 1e-9;

double DEG_to_RAD(double d) { return d*M_PI/180.0; }
double RAD_to_DEG(double r) { return r*180.0/M_PI; }

struct point_i {    //  Punto con coordenadas de valores enteros
    int x, y;
    point_i() { x = y = 0; }
    point_i(int _x, int _y) : x(_x), y(_y) {}
};

struct point {      // Punto con coordenadas de valores reales
    double x, y;
    point() { x = y = 0.0; }
    point(double _x, double _y) : x(_x), y(_y) {}
    bool operator < (point other) const {
        if (fabs(x-other.x) > EPS)
            return x < other.x;
        return y < other.y;
    }
    bool operator == (point other) const {
        return (fabs(x-other.x) < EPS && (fabs(y-other.y) < EPS));
    }
};

double dist(point p1, point p2) {                   // Distancia euclidiana
    // hypot(dx, dy) returns sqrt(dx*dx + dy*dy)
    return hypot(p1.x-p2.x, p1.y-p2.y);
}

// Rota el punto p theta grados en ccw con respecto al origen (0, 0)
point rotate(point p, double theta) {
    double rad = DEG_to_RAD(theta);
    return point(p.x*cos(rad) - p.y*sin(rad),  p.x*sin(rad) + p.y*cos(rad));
}

struct line { double a, b, c; };                 // Linea con la ecuacion ax + by + c = 0

// Convierte 2 puntos a una linea y la guarda en la linea pasada por referencia
void pointsToLine(point p1, point p2, line &l) {
    if (fabs(p1.x-p2.x) < EPS)                      // Linea vertical
        l = {1.0, 0.0, -p1.x};                      // Valores default
    else {
        double a = -(double)(p1.y-p2.y) / (p1.x-p2.x);
        l = {a, 1.0, -(double)(a*p1.x) - p1.y};     // Nota: b siempre es 1.0
    }
}

bool areParallel(line l1, line l2) {             // Checa a & b
    return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS);
}

bool areSame(line l1, line l2) {                 // Tambien checa c
    return areParallel(l1 ,l2) && (fabs(l1.c-l2.c) < EPS);
}

// Retorna true y el punto de intereseccion p, si 2 lineas se intersecan
bool areIntersect(line l1, line l2, point &p) {
    if (areParallel(l1, l2)) return false;         // No hay interseccion
    // Resuelve un sistema de 2 ecuaciones lineales con 2 incognitas
    p.x = (l2.b*l1.c - l1.b*l2.c) / (l2.a*l1.b - l1.a*l2.b);
    // Caso especial: prueba si es linea vertical para evitar la division entre 0
    if (fabs(l1.b) > EPS) p.y = -(l1.a*p.x + l1.c);
    else                  p.y = -(l2.a*p.x + l2.c);
    return true;
}

struct vec {    // Vector
    double x, y;
    vec(double _x, double _y) : x(_x), y(_y) {}
};

vec toVec(const point &a, const point &b) { return vec(b.x-a.x, b.y-a.y); }         // Convierte 2 puntos en el vector a->b

vec scale(const vec &v, double s) { return vec(v.x*s, v.y*s); }                     // Escala un vector por el valor s

point translate(const point &p, const vec &v) { return point(p.x+v.x, p.y+v.y); }   // Traslada p, de acuerdo a v

// Convierte un punto y una pendiente en una linea
void pointSlopeToLine(point p, double m, line &l) {
    l.a = -m;                                      // Siempre -m
    l.b = 1;                                       // Siempre 1
    l.c = -((l.a * p.x) + (l.b * p.y));            // Se calcula esto
}

void closestPoint(line l, point p, point &ans) {
    // Esta linea es perpendicular a l y pasa a traves de p
    line perpendicular;                            
    if (fabs(l.b) < EPS) {                         // Linea vertical
        ans.x = -(l.c);
        ans.y = p.y;
        return;
    }
    if (fabs(l.a) < EPS) {                         // Linea horizontal
        ans.x = p.x;
        ans.y = -(l.c);
        return;
    }
    pointSlopeToLine(p, 1/l.a, perpendicular);     // Linea normal
    // Se interseca la linea l con esta linea perpendicular y el punto de interseccion es el punto mas cercano
    areIntersect(l, perpendicular, ans);
}

// Retorna la reflexion de un punto sobre una linea
void reflectionPoint(line l, point p, point &ans) {
    point b;
    closestPoint(l, p, b);
    vec v = toVec(p, b);
    ans = translate(translate(p, v), v);           // Traslada p 2 veces
}

// Retorna el producto punto entre los vectores a & b
double dot(vec a, vec b) { return (a.x*b.x + a.y*b.y); }

// Retorna el cuadrado de la magnitud de un vector
double norm_sq(vec v) { return v.x*v.x + v.y*v.y; }

double angle(const point &a, const point &o, const point &b) {
    vec oa = toVec(o, a), ob = toVec(o, b);        // a != o != b
    return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}                                                // Angulo aob en radianes

// Retorna la distancia desde un punto p a una linea definida por 2 punto a & b (deben ser diferentes)
// El punto mas cercano se guarda en el punto c
double distToLine(point p, point a, point b, point &c) {
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    // Formula: c = a + u*ab
    c = translate(a, scale(ab, u));                // Traslada el punto a al punto c
    return dist(p, c);                             // Distancia euclidiana
}

// Retorna la distancia desde un punto p a un segmento de linea ab, definido por 2 puntos a & b (deben ser diferentes)
// El punto mas cercano se guarda en el punto c
double distToLineSegment(point p, point a, point b, point &c) {
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    if (u < 0.0) {                                  // Mas cercano al punto a
        c = point(a.x, a.y);
        return dist(p, a);
    }
    if (u > 1.0) {                                 // Mas cercano al punto b
        c = point(b.x, b.y);
        return dist(p, b);
    }
    return distToLine(p, a, b, c);                 // Se usa distToLine
}

// Retorna el producto cruz entre 2 vectores a & b
double cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }

// Retorna 2 veces el area del triangulo A-B-C
// int area2(point p, point q, point r) {
//   return p.x * q.y - p.y * q.x +
//          q.x * r.y - q.y * r.x +
//          r.x * p.y - r.y * p.x;
// }

// Nota: Para aceptar puntos colineares, se debe cambiar el "> 0"
// Retorna true si el punto r se encuentra al lado izquierdo de la linea pq
bool ccw(point p, point q, point r) { return cross(toVec(p, q), toVec(p, r)) > -EPS; }

// Retorna true si el punto r esta en la linea pq
bool collinear(point p, point q, point r) { return fabs(cross(toVec(p, q), toVec(p, r))) < EPS; }
