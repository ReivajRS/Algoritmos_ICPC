// Time complexity O(n)
typedef vector<int> vi;

int main(){
    int n = 6, arr[] = {7, 1, 4, 3, 5, 2};

    stack<int> st;
    vi nextGreater(n, -1);  // Para cada posicion se guarda cual es el siguiente elemento mayor

    for(int i=0; i<n; i++){
        while(!st.empty() && arr[i] > arr[st.top()]){   // Mientras la pila no este vacia y el i-esimo elemento sea mayor al top
            nextGreater[st.top()] = arr[i];             // El siguiente mayor del elemento en el top es el elemento en la i-esima posicion
            st.pop();                                   // Se saca el elemento del top
        }
        st.push(i);                                     // Se inserta la i-esima posicion en la pila
    }
	/*	Notas:
        - Para obtener los mayores previos, se hace un for reverso
        - Para obtener los menores, solo se invierte la segunda condicion en el ciclo while
    */
}