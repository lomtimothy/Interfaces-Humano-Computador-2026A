#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

class LeastSquaredRegressor {
private:
    vector<vector<double>> X;
    vector<double> y;
    vector<double> beta;

    vector<vector<double>> transponer(const vector<vector<double>>& matriz) {
        int filas = matriz.size();
        int columnas = matriz[0].size();
        vector<vector<double>> trans(columnas, vector<double>(filas));
        
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                trans[j][i] = matriz[i][j];
            }
        }
        return trans;
    }

    vector<vector<double>> multiplicar(const vector<vector<double>>& A, const vector<vector<double>>& B) {
        int filasA = A.size();
        int colA = A[0].size();
        int colB = B[0].size();
        vector<vector<double>> resultado(filasA, vector<double>(colB, 0.0));

        for (int i = 0; i < filasA; ++i) {
            for (int j = 0; j < colB; ++j) {
                for (int k = 0; k < colA; ++k) {
                    resultado[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return resultado;
    }

    vector<double> multiplicar(const vector<vector<double>>& A, const vector<double>& v) {
        int filas = A.size();
        int columnas = A[0].size();
        vector<double> resultado(filas, 0.0);

        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                resultado[i] += A[i][j] * v[j];
            }
        }
        return resultado;
    }

    vector<vector<double>> inversa3x3(const vector<vector<double>>& m) {
        double det = m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) -
                     m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
                     m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);

        if (det == 0) {
            cout << "Error: La matriz no tiene inversa." << endl;
            return m;
        }

        vector<vector<double>> inv(3, vector<double>(3));
        double invdet = 1.0 / det;

        inv[0][0] = (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * invdet;
        inv[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * invdet;
        inv[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invdet;
        inv[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * invdet;
        inv[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * invdet;
        inv[1][2] = (m[1][0] * m[0][2] - m[0][0] * m[1][2]) * invdet;
        inv[2][0] = (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * invdet;
        inv[2][1] = (m[2][0] * m[0][1] - m[0][0] * m[2][1]) * invdet;
        inv[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * invdet;

        return inv;
    }

public:
    LeastSquaredRegressor() {
        X = {
            {1, 41.9, 29.1}, {1, 43.4, 29.3}, {1, 43.9, 29.5}, {1, 44.5, 29.7},
            {1, 47.3, 29.9}, {1, 47.5, 30.3}, {1, 47.9, 30.5}, {1, 50.2, 30.7},
            {1, 52.8, 30.8}, {1, 53.2, 30.9}, {1, 56.7, 31.5}, {1, 57.0, 31.7},
            {1, 63.5, 31.9}, {1, 65.3, 32.0}, {1, 71.1, 32.1}, {1, 77.0, 32.5},
            {1, 77.8, 32.9}
        };

        y = {
            251.3, 251.3, 248.3, 267.5, 273.0, 276.5, 270.3, 274.9,
            285.0, 290.0, 297.0, 302.5, 304.5, 309.3, 321.7, 330.7, 349.0
        };
    }

    void entrenar() {
        vector<vector<double>> X_T = transponer(X);
        vector<vector<double>> X_T_X = multiplicar(X_T, X);
        vector<vector<double>> inv_X_T_X = inversa3x3(X_T_X);
        vector<double> X_T_y = multiplicar(X_T, y);
        beta = multiplicar(inv_X_T_X, X_T_y);
    }

    void imprimirEcuacion() {
        if (beta.empty()) {
            cout << "El modelo no ha sido entrenado aun." << endl;
            return;
        }
        cout << fixed << setprecision(2); 
        cout << "--- ECUACION DE REGRESION ---" << endl;
        cout << "Yield = " << beta[0] << " + (" << beta[1] << " * x1) + (" << beta[2] << " * x2)" << endl;
        cout << "-----------------------------\n" << endl;
    }

    void simularExperimentos() {
        if (beta.empty()) return;

        cout << "--- SIMULACION DE 5 EXPERIMENTOS ---" << endl;
        
        double casos_x1[] = {55.0, 60.0, 40.0, 80.0, 50.0};
        double casos_x2[] = {30.0, 31.0, 28.0, 33.0, 30.5};

        for (int i = 0; i < 5; ++i) {
            double x1 = casos_x1[i];
            double x2 = casos_x2[i];
            double yield_predicho = beta[0] + (beta[1] * x1) + (beta[2] * x2);
            
            cout << "Exp " << i + 1 << " [Elemento x1=" << x1 << ", Elemento x2=" << x2 << "] -> ";
            cout << "Yield predicho = " << yield_predicho << " unidades de dureza/flexibilidad" << endl;
        }
    }
};

int main() {
    LeastSquaredRegressor modelo;

    modelo.entrenar();

    modelo.imprimirEcuacion();

    modelo.simularExperimentos();

    return 0;
}