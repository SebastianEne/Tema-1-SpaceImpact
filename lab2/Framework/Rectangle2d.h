#pragma once
#include "Object2D.h"


class Rectangle2D:public Object2D
{
public:
	Rectangle2D(Point2D p, float width, float height)
	{
		fill = false;
		color.r = color.b = color.r = 0;
		type = 2;

		//adauga cele patru puncte ale dreptunghiului
		points.push_back(new Point2D(p.x,p.y));
		transf_points.push_back(new Point2D(p.x,p.y));
		Point2D *p2 = new Point2D(); p2->x = p.x + width;  p2->y = p.y;
		points.push_back(p2);
		transf_points.push_back(new Point2D(p2->x,p2->y));
		Point2D *p3 = new Point2D(); p3->x = p2->x; p3->y = p2->y + height;
		points.push_back(p3);
		transf_points.push_back(new Point2D(p3->x,p3->y));
		Point2D *p4 = new Point2D(); p4->x = p.x; p4->y = p.y + height;
		points.push_back(p4);
		transf_points.push_back(new Point2D(p4->x,p4->y));
	}


	Rectangle2D(Point2D p, float width, float height, Color _color, bool _fill)
	{
		fill = _fill;
		color.r = _color.r;
		color.g = _color.g;
		color.b = _color.b;
		type = 2;

		//adauga cele patru puncte ale dreptunghiului
		points.push_back(new Point2D(p.x,p.y));
		transf_points.push_back(new Point2D(p.x,p.y));
		Point2D *p2 = new Point2D(); p2->x = p.x + width;  p2->y = p.y;
		points.push_back(p2);
		transf_points.push_back(new Point2D(p2->x,p2->y));
		Point2D *p3 = new Point2D(); p3->x = p2->x; p3->y = p2->y + height;
		points.push_back(p3);
		transf_points.push_back(new Point2D(p3->x,p3->y));
		Point2D *p4 = new Point2D(); p4->x = p.x; p4->y = p.y + height;
		points.push_back(p4);
		transf_points.push_back(new Point2D(p4->x,p4->y));
	}

	void LoadTexture(char *filename, int type) {

		if(type == 1) 
		{
			TGAImg texture;
		
			if(texture.Load(filename) != IMG_OK ) {
				printf("Nu se poate deschide textura %s, fisierul nu e pe disc\n", filename);
				o_texture = false;
			}

			glGenTextures(1, &TexId);
			glBindTexture(GL_TEXTURE_2D, TexId);

			if(texture.GetBPP() == 24)			// verfic daca are 24 biti pe pixel
				glTexImage2D(GL_TEXTURE_2D, 0, 3, texture.GetWidth(),
												  texture.GetHeight(),
												  0,
												  GL_RGB,
												  GL_UNSIGNED_BYTE,
												  texture.GetImg());
			else if(texture.GetBPP() == 32) 
				glTexImage2D(GL_TEXTURE_2D, 0, 4, texture.GetWidth(), 
												  texture.GetHeight(),
												  0,
												  GL_RGBA,
												  GL_UNSIGNED_BYTE,
												  texture.GetImg());
			else {
					printf("Formatul texturii %s nu e acceptat\n", filename);
					o_texture = false;
			}
			
		   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
		   o_texture = true;	
		}
		else if(type == 2)
		{
		  std::vector<unsigned char> png;
		  char *buffer;
		  std::vector<unsigned char> image; //the raw pixels
		  unsigned width, height;
		  int i;

		  //load and decode
		  lodepng::load_file(png, filename);
		  unsigned error = lodepng::decode(image, width, height, png);
		  buffer = new char[image.size()];

		  for(i=0; i<image.size(); i++) {
			buffer[i] = image[i];
		  }
		  glEnable(GL_ALPHA_TEST);
		  glAlphaFunc(GL_GREATER, 0.1);
		  glGenTextures(1, &TexId);
		  glBindTexture(GL_TEXTURE_2D, TexId);
		  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA8, width,
											height,
											0,
											GL_RGBA,
											GL_UNSIGNED_BYTE,
											buffer);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
		  o_texture = true;
		}
	}

	~Rectangle2D() {}

};