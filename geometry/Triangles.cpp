// NOTA: Para las siguientes funciones se deben agregar los elementos de puntos, lineas y vectores necesarios

const double EPS = 1e-9;

double perimeter(double ab, double bc, double ca) { return ab + bc + ca; }

double perimeter(point a, point b, point c) { return dist(a, b) + dist(b, c) + dist(c, a); }

double area(double ab, double bc, double ca) {      // Formula de Heron
    double s = 0.5 * perimeter(ab, bc, ca);
    return sqrt(s) * sqrt(s-ab) * sqrt(s-bc) * sqrt(s-ca);
}

double area(point a, point b, point c) { return area(dist(a, b), dist(b, c), dist(c, a)); }

// Retorna el radio del circulo que se forma tocando los lados de un triangulo
double rInCircle(double ab, double bc, double ca) { return area(ab, bc, ca) / (0.5 * perimeter(ab, bc, ca)); }

double rInCircle(point a, point b, point c) { return rInCircle(dist(a, b), dist(b, c), dist(c, a)); }

/*
    Retorna 1 si hay un centro del inCircle, retorna 0 de otra manera,
    si se retorna 1, ctr sera el centro del inCircle y r es el radio del mismo
*/
int inCircle(point p1, point p2, point p3, point &ctr, double &r) {
    r = rInCircle(p1, p2, p3);
    if (fabs(r) < EPS) return 0;                   // No hay centro

    line l1, l2;                    // Calcula los 2 angulos bisectores
    double ratio = dist(p1, p2) / dist(p1, p3);
    point p = translate(p2, scale(toVec(p2, p3), ratio / (1 + ratio)));
    pointsToLine(p1, p, l1);

    ratio = dist(p2, p1) / dist(p2, p3);
    p = translate(p1, scale(toVec(p1, p3), ratio / (1 + ratio)));
    pointsToLine(p2, p, l2);

    areIntersect(l1, l2, ctr);           // Obtiene su punto de interseccion
    return 1;
}

// Retorna el radio del circulo en el que su circunferencia toca los 3 puntos del triangulo
double rCircumCircle(double ab, double bc, double ca) { return ab * bc * ca / (4.0 * area(ab, bc, ca)); }

double rCircumCircle(point a, point b, point c) { return rCircumCircle(dist(a, b), dist(b, c), dist(c, a)); }

/*
    Retorna 1 si hay un centro del circumCircle, retorna 0 de otra manera
    si se retorna 1, ctr sera el centro del circumCircle y r es el radio del mismo
*/
int circumCircle(point p1, point p2, point p3, point &ctr, double &r){
    double a = p2.x - p1.x, b = p2.y - p1.y;
    double c = p3.x - p1.x, d = p3.y - p1.y;
    double e = a * (p1.x + p2.x) + b * (p1.y + p2.y);
    double f = c * (p1.x + p3.x) + d * (p1.y + p3.y);
    double g = 2.0 * (a * (p3.y - p2.y) - b * (p3.x - p2.x));
    if (fabs(g) < EPS) return 0;

    ctr.x = (d*e - b*f) / g;
    ctr.y = (a*f - c*e) / g;
    r = dist(p1, ctr);  // r = distancia del centro a 1 de los 3 puntos
    return 1;
}

// Retorna true si el punto d esta dentro del circumCircle definido por a, b, c
int inCircumCircle(point a, point b, point c, point d) {
    return (a.x - d.x) * (b.y - d.y) * ((c.x - d.x) * (c.x - d.x) + (c.y - d.y) * (c.y - d.y)) +
        (a.y - d.y) * ((b.x - d.x) * (b.x - d.x) + (b.y - d.y) * (b.y - d.y)) * (c.x - d.x) +
        ((a.x - d.x) * (a.x - d.x) + (a.y - d.y) * (a.y - d.y)) * (b.x - d.x) * (c.y - d.y) -
        ((a.x - d.x) * (a.x - d.x) + (a.y - d.y) * (a.y - d.y)) * (b.y - d.y) * (c.x - d.x) -
        (a.y - d.y) * (b.x - d.x) * ((c.x - d.x) * (c.x - d.x) + (c.y - d.y) * (c.y - d.y)) -
        (a.x - d.x) * ((b.x - d.x) * (b.x - d.x) + (b.y - d.y) * (b.y - d.y)) * (c.y - d.y) > 0 ? 1 : 0;
}

// Retorna si 3 lados pueden formar un triangulo
bool canFormTriangle(double a, double b, double c) { return (a+b > c) && (a+c > b) && (b+c > a); }