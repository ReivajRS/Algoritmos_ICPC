struct Point {
    double x, y, z;
    Point() {}
    Point(double xx, double yy, double zz) { x = xx, y = yy, z = zz; }
    // Operadores escalares
    Point operator*(double f) { return Point(x * f, y * f, z * f); }
    Point operator/(double f) { return Point(x / f, y / f, z / f); }
    // Operadores P3
    Point operator-(Point p) { return Point(x - p.x, y - p.y, z - p.z); }
    Point operator+(Point p) { return Point(x + p.x, y + p.y, z + p.z); }
    Point operator%(Point p) { return Point(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x); }  /// (|p||q|sin(ang))* normal
    double operator|(Point p) { return x * p.x + y * p.y + z * p.z; }
    // Comparadores
    bool operator==(Point p) { return tie(x, y, z) == tie(p.x, p.y, p.z); }
    bool operator!=(Point p) { return !operator==(p); }
    bool operator<(Point p) { return tie(x, y, z) < tie(p.x, p.y, p.z); }
};
    Point zero = Point(0, 0, 0);

    // BASICAS
    double sq(Point p) { return p | p; }
    double abs(Point p) { return sqrt(sq(p)); }
    Point unit(Point p) { return p / abs(p); }

    // ANGULOS
    double angle(Point p, Point q) {  ///[0, pi]
    double co = (p | q) / abs(p) / abs(q);
        return acos(max(-1.0, min(1.0, co)));
    }
    double small_angle(Point p, Point q) {  ///[0, pi/2]
        return acos(min(abs(p | q) / abs(p) / abs(q), 1.0))
    }

    // 3D - ORIENTACION
    double orient(Point p, Point q, Point r, Point s) { return (q - p) % (r - p) | (s - p); }
    bool coplanar(Point p, Point q, Point r, Point s) {
    return abs(orient(p, q, r, s)) < eps;
    }
    bool skew(Point p, Point q, Point r, Point s) { // Skew = No se intersecan ni son paralelas
    return abs(orient(p, q, r, s)) > eps;           // Lineas: PQ, RS
    }
    double orient_norm(Point p, Point q, Point r, Point n) {    // n := normal to a given plane PI n = normal al plano dado PI
    return (q - p) % (r - p) | n;                               // Equivalente al producto cruz 2D sobre PI (De la proyeccion ortogonal)
}