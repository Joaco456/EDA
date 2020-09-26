#ifndef PUNTO_H
#define PUNTO_H

class Punto
{
public:
	Punto()
	{
		x = 0;
		y = 0;
		z = 0;
	}
	Punto(float a, float b, float c)
	{
		x = a;
		y = b;
		z = c;
	}
	Punto(float a, float b)
	{
		x = a;
		y = b;
		z = 0.0;
	}

	float x, y, z;
};

#endif // PUNTO_H