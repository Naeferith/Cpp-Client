// Client.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>

#include "Shape.h"

using namespace std;

int main()
{
	vector<Vector2D> sommets = {
		Vector2D(-1, 1),
		Vector2D(1, 1),
		Vector2D(1, -1),
		Vector2D(-1, -1)
	};

	Shape carre(sommets, &Color::BLUE);


	system("pause");
	return 0;
}

