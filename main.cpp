#include "geometry.h"
#include <locale>

using std::cin;
using std::cout;
using std::endl;

int main() {
    system("chcp 65001 > nul");

    ShapeTriangle triangle;
    cout << "Введіть координати трикутника (x1 y1 x2 y2 x3 y3): ";
    cin >> triangle.p1.xCoord >> triangle.p1.yCoord
        >> triangle.p2.xCoord >> triangle.p2.yCoord
        >> triangle.p3.xCoord >> triangle.p3.yCoord;

    cout << "Трикутник з вершинами: A(" << triangle.p1.xCoord << ", " << triangle.p1.yCoord
         << "), B(" << triangle.p2.xCoord << ", " << triangle.p2.yCoord
         << "), C(" << triangle.p3.xCoord << ", " << triangle.p3.yCoord << ")" << endl;

    if (triangle.isFlat()) {
        cout << "Це вироджений трикутник!" << endl;
    }

    int option = 0;

    while (true) {
        cout << "Оберіть метод перевірки точки:" << endl;
        cout << "1. Через площу (методичка) 2. Через векторний добуток" << endl;
        cin >> option;

        if (cin.fail()) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Введення некоректне. Спробуйте знову." << endl;
            continue;
        }

        if (option == 1 || option == 2) break;
        cout << "Будь ласка, введіть 1 або 2." << endl;
    }

    int pointCount;
    while (true) {
        cout << "Скільки точок потрібно перевірити?: ";
        cin >> pointCount;

        if (cin.fail()) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Некоректне введення. Введіть додатне число." << endl;
            continue;
        }
        if (pointCount > 0) break;
        cout << "Кількість має бути додатною!" << endl;
    }

    for (int i = 0; i < pointCount; ++i) {
        Coord pt;
        cout << "Введіть координати точки (x y): ";
        cin >> pt.xCoord >> pt.yCoord;

        double eps = 1e3;
        pt.xCoord = round(pt.xCoord * eps) / eps;
        pt.yCoord = round(pt.yCoord * eps) / eps;

        cout << "Точка з координатами: " << pt.xCoord << ", " << pt.yCoord << endl;

        if ((pt.xCoord == triangle.p1.xCoord && pt.yCoord == triangle.p1.yCoord) ||
            (pt.xCoord == triangle.p2.xCoord && pt.yCoord == triangle.p2.yCoord) ||
            (pt.xCoord == triangle.p3.xCoord && pt.yCoord == triangle.p3.yCoord)) {
            cout << "Ця точка збігається з вершиною трикутника." << endl;
        }
        else if (isOnEdge(pt, triangle.p1, triangle.p2) ||
                 isOnEdge(pt, triangle.p2, triangle.p3) ||
                 isOnEdge(pt, triangle.p3, triangle.p1)) {
            cout << "Точка лежить на стороні трикутника." << endl;
        }
        else if ((option == 1 && triangle.isInside(pt)) ||
                 (option == 2 && triangle.isInsideByVector(pt))) {
            cout << "Точка знаходиться всередині трикутника." << endl;
        } else {
            cout << "Точка поза трикутником." << endl;
        }
    }

    return 0;
}
