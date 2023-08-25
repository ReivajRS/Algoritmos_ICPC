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
};

// Regresa si el punto p se encuentra dentro del circulo con centro c y radio r
int insideCircle(point_i p, point_i c, int r) {
    int dx = p.x-c.x, dy = p.y-c.y;
    int Euc = dx*dx + dy*dy, rSq = r*r;
    return Euc < rSq ? 1 : Euc == rSq ? 0 : -1; // dentro/borde/fuera
}

/* 
    Retorna si se intersecan 2 circulos de radio r con centro p1 y p2
    Si se intersecan, se obtiene el punto donde lo hacen en c
    Para obtener el segundo punto de interseccion, se invierten p1 y p2
*/
bool circle2PtsRad(point p1, point p2, double r, point &c) {
    double d2 = (p1.x-p2.x) * (p1.x-p2.x) + (p1.y-p2.y) * (p1.y-p2.y);
    double det = r*r / d2 - 0.25;
    if (det < 0.0) return false;
    double h = sqrt(det);
    c.x = (p1.x+p2.x) * 0.5 + (p1.y-p2.y) * h;
    c.y = (p1.y+p2.y) * 0.5 + (p2.x-p1.x) * h;
    return true;
}

// Retorna la longitud del arco formado por una circunferencia c y un angulo central de theta°
double arcLength(double c, double theta) { return theta/360.0 * c; }

// Retorna la longitud de la cuerda formada por un circulo de area A y un angulo central de theta°
double chordLength(double A, double theta) { return sqrt(A * (1 - cos(DEG_to_RAD(theta)))); }

// Retorna el area de un sector de theta° del circulo
double sectorArea(double A, double theta) { return A/360.0 * A; }