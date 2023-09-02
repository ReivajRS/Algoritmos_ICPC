const double EPS = 1e-9;

// NOTA: Para las siguientes funciones se deben agregar los elementos de puntos y vectores necesarios

/*
    Retorna el perimetro del poligono P, que es la suma de las distancias Euclideanas
    de los segmentos consecutivos de lineas (aristas del poligono)
*/
double perimeter(const vector<point> &P) {
    double ans = 0.0;
    for (int i = 0; i < (int)P.size()-1; ++i)      // Nota: P[n-1] = P[0]
        ans += dist(P[i], P[i+1]);
    return ans;
}

// Retorna el area del poligono P haciendo uso de la Shoelace formula
double area(const vector<point> &P) {
    double ans = 0.0;
    for (int i = 0; i < (int)P.size()-1; ++i)
        ans += (P[i].x*P[i+1].y - P[i+1].x*P[i].y);
    return fabs(ans)/2.0;
}

// Calculo del area del poligono P escrito en operaciones con vectores
double area_alternative(const vector<point> &P) {
    double ans = 0.0; point O(0.0, 0.0);           // O = El origen
    for (int i = 0; i < (int)P.size()-1; ++i)      // Suma de las areas
        ans += cross(toVec(O, P[i]), toVec(O, P[i+1]));
    return fabs(ans)/2.0;
}

/*
    Retorna true si el poligono es convexo, lo que se determina si siempre se hace
    una vuelta hacia el mismo lado, mientras se analizan las aristas del poligono una por una
*/
bool isConvex(const vector<point> &P) {
    int n = (int)P.size();
    // Un point/sz=2 o una linea/sz=3 no es convexo
    if (n <= 3) return false;
    bool firstTurn = ccw(P[0], P[1], P[2]);
    for (int i = 1; i < n-1; ++i)
        if (ccw(P[i], P[i+1], P[(i+2) == n ? 1 : i+2]) != firstTurn)
        return false;                              // Concavo
    return true;                                   // Convexo
}

/*
    Segun el punto pt, retorna 1 si esta dentro del poligono P, 0 si esta sobre
    un vertice o arista, y -1 si esta fuera del poligono
*/
int insidePolygon(point pt, const vector<point> &P) {
    int n = (int)P.size();
    if (n <= 3) return -1;                         // Evitar un punto o una linea
    bool on_polygon = false;
    for (int i = 0; i < n-1; ++i)                  // Sobre vertice/arista
        if (fabs(dist(P[i], pt) + dist(pt, P[i+1]) - dist(P[i], P[i+1])) < EPS)
        on_polygon = true;
    if (on_polygon) return 0;                      // pt esta sobre el poligono
    double sum = 0.0;                              // Primer = Ultimo punto
    for (int i = 0; i < n-1; ++i) {
        if (ccw(pt, P[i], P[i+1]))
        sum += angle(P[i], pt, P[i+1]);            // Vuelta a la izquierda/ccw
        else
        sum -= angle(P[i], pt, P[i+1]);            // Vuelta a la derecha/cw
    }
    return fabs(sum) > M_PI ? 1 : -1;              // 360d->dentro, 0d->fuera
}

// Retorna el punto de interseccion entre el segmento p-q y la linea A-B
point lineIntersectSeg(point p, point q, point A, point B) {
    double a = B.y-A.y, b = A.x-B.x, c = B.x*A.y - A.x*B.y;
    double u = fabs(a*p.x + b*p.y + c);
    double v = fabs(a*q.x + b*q.y + c);
    return point((p.x*v + q.x*u) / (u+v), (p.y*v + q.y*u) / (u+v));
}

/*
    Corta el poligono Q a traves de la linea formada por punto A->Punto B (El orden importa)
    EL poligono que se retorna es el poligono que queda en la parte izquierda del corte
    Nota: EL ultimo punto debe de ser igual al primero
*/
vector<point> cutPolygon(point A, point B, const vector<point> &Q) {
    vector<point> P;
    for (int i = 0; i < (int)Q.size(); ++i) {
        double left1 = cross(toVec(A, B), toVec(A, Q[i])), left2 = 0;
        if (i != (int)Q.size()-1) left2 = cross(toVec(A, B), toVec(A, Q[i+1]));
        if (left1 > -EPS) P.push_back(Q[i]);         // Q[i] esta a la izquierda
        if (left1*left2 < -EPS)                      // Cruza la linea AB
        P.push_back(lineIntersectSeg(Q[i], Q[i+1], A, B));
    }
    if (!P.empty() && !(P.back() == P.front()))
        P.push_back(P.front());                      // wrap around Envolver
    return P;
}

vector<point> CH_Graham(vector<point> &Pts) {       // O(n log n)
    vector<point> P(Pts);
    int n = (int)P.size();
    if (n <= 3) {                                   // punto/linea/triangulo
        if (!(P[0] == P[n-1])) P.push_back(P[0]);   // Caso esquina
        return P;                                   // EL CH es P
    }

    // Primer paso, hallar P0 = punto con la menor Y, y en caso de empate, la X mayor. O(n log n)
    int P0 = min_element(P.begin(), P.end())-P.begin();
    swap(P[0], P[P0]);                             // swap P[P0] y P[0]

    // Segundo paso, ordenar los puntos por su angulo alrededor de P0
    sort(++P.begin(), P.end(), [&](point a, point b) {
        return ccw(P[0], a, b);                      // Se usa P[0] como el pivote
    });

    // Tercer paso, las pruebas de ccw. O(n)
    vector<point> S({P[n-1], P[0], P[1]});          // S inicial
    int i = 2;                                      // Checamos el resto
    while (i < n) {                                 // n > 3, O(n)
        int j = (int)S.size()-1;
        if (ccw(S[j-1], S[j], P[i]))                // Vuelta CCW
            S.push_back(P[i++]);                    // Se acepta este punto
        else                                        // Vuelta CW
            S.pop_back();                           // Pop hasta que haya una vuelta CCW
    }
    return S;
}

vector<point> CH_Andrew(vector<point> &Pts) {       // O(n log n)
    int n = Pts.size(), k = 0;
    vector<point> H(2*n);
    sort(Pts.begin(), Pts.end());                   // Ordenar los puntos por x/y
    for (int i = 0; i < n; ++i) {                   // Construir el hull de abajo
        while ((k >= 2) && !ccw(H[k-2], H[k-1], Pts[i])) --k;
        H[k++] = Pts[i];
    }
    for (int i = n-2, t = k+1; i >= 0; --i) {       // Construir el hull de arriba
        while ((k >= t) && !ccw(H[k-2], H[k-1], Pts[i])) --k;
        H[k++] = Pts[i];
    }
    H.resize(k);
    return H;
}