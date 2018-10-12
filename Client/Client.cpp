// Client.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include <WinSock2.h>

#include "Circle.h"
#include "ShapeGroup.h"

#define _DEBUG_GRAPHIC_

using namespace std;

int main()
{

#ifdef _DEBUG_GRAPHIC_
	vector<Vector2D> sommets = {
		Vector2D(-1, 1),
		Vector2D(1, 1),
		Vector2D(1, -1),
		Vector2D(-1, -1),
	};

	ShapeGroup group;
	Circle cercle(Vector2D(1,1), 2, &Color::GREEN);
	//Shape carre(sommets, &Color::BLUE);

	//group + carre; bug

	//carre.Rotate(Vector2D(0, 0), 1.5708);
#endif

#ifdef _DEBUG_NETWORK_
	int r;
#endif // _DEBUG_NETWORK_


	system("pause");
	return 0;
}

