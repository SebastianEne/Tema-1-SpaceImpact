#pragma once
#include "Point2D.h"
#include <vector>


using namespace std;

//obiect generic 2D ajutator - ca sa pun toate obiectele (puncte, linii, dreptunghi, circle, polygon)
//in sistemul de coordonate, pentru a fi desenate
class Object2D
{
public:
	vector <Point2D*> points;
	vector <Point2D*> transf_points;
	vector <Point2D*> texture_coords;  

	int type; //1 = linie; 2 = dreptunghi; 3=cerc; 4=poligon
	GLuint TexId;
	Color color;
	bool fill;
	bool o_texture;
	bool lock;
	float angle;

public:
	Object2D() {
		angle = 0;
		lock = false;
		texture_coords.push_back(new Point2D(0.0f, 1.0f));
		texture_coords.push_back(new Point2D(1.0f, 1.0f));
		texture_coords.push_back(new Point2D(1.0f, 0.0f));
		texture_coords.push_back(new Point2D(0.0f, 0.0f));
	}

	void changeLock()
	{
		lock = !lock;
	}

	Object2D(vector <Point2D*> _points,int _type,Color _color,bool _fill)
	{
		for (int i = 0; i < _points.size(); i++)
		{
			points.push_back(new Point2D(_points[i]->x,_points[i]->y));
			transf_points.push_back(new Point2D(_points[i]->x,_points[i]->y));
		}
		type = _type;
		color = _color;
		fill = _fill;
	}


	~Object2D() {}
};