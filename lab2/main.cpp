#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include <iostream>
#include <windows.h>
#include <time.h>


#define PI 3.14159265358979323846

using namespace std;

Visual2D *v2d1, *v2d2;
Rectangle2D *rect, *player, *effect, *enemy[5], *healthbar[3], *gameover, *bullet[10];
Transform2D *tr;
Text *text[5];
BYTE move_keys;
Point2D g;
float  enemy_angle[5];
int split_frames = 1, frames;
unsigned int life = 2, score;
bool explosion_effect;
char score_buffer[5]	


void affectLife(Object2D *o) {
	int j;

	if(o == player)
	{
				explosion_effect = true;	
				tr->setTheNewG(player, effect);

					DrawingWindow::removeObject2D(healthbar[life]);				
					if(life > 0) life--;
					else if(life == 0) {
						
						text[0]->color = Color(255, 255, 255);	
						DrawingWindow::removeObject2D(rect);
						DrawingWindow::removeText(text[0]);
						DrawingWindow::removeObject2D(player);
						DrawingWindow::removeObject2D(enemy[0]);
						DrawingWindow::removeObject2D(enemy[1]);
						DrawingWindow::removeObject2D(enemy[2]);
						DrawingWindow::removeObject2D(enemy[3]);
						DrawingWindow::removeObject2D(bullet[0]);
						DrawingWindow::removeObject2D(enemy[4]);
						DrawingWindow::addObject2D(gameover);		
					}
	}
	else {
				explosion_effect = true;	
				tr->setTheNewG(o, effect);	
				score = score + 50;
				text[1]->text = itoa(score, score_buffer,10);
				DrawingWindow::removeObject2D(o);
				o->lock = true;

	}
}

void moveEnemy() 
{

	for(int i=1; i<=4; i++)
	{
		tr->loadIdentityMatrix();
		tr->translateMatrix(2*sin(enemy[i]->angle), 2*cos(enemy[i]->angle));
		tr->applyTransform_o(enemy[i]);
	}

}

void addTextures() 
{
	rect->LoadTexture("textures/background.png",2);
	player->LoadTexture("textures/player.png",2);
	enemy[1]->LoadTexture("textures/enemy_1.png", 2);
	enemy[2]->LoadTexture("textures/enemy_2.png", 2);
	enemy[3]->LoadTexture("textures/enemy_3.png", 2);
	enemy[4]->LoadTexture("textures/enemy_4.png", 2);
	effect->LoadTexture("textures/explosions.png",2);
	healthbar[0]->LoadTexture("textures/heart.png", 2);
	healthbar[1]->LoadTexture("textures/heart.png", 2);
	healthbar[2]->LoadTexture("textures/heart.png", 2);
	gameover->LoadTexture("textures/gameover.png", 2);
	bullet[0]->LoadTexture("textures/bullet.png",2);
	tr->loadIdentityMatrix();
	tr->scaleMatrix(1.6,1.6);
	tr->applyTransformTextures(bullet[0]);
}

void DrawingWindow::init()
{
	
	v2d1 = new Visual2D(0,0,DrawingWindow::width,DrawingWindow::height,0,0,DrawingWindow::width,DrawingWindow::height);  
	addVisual2D(v2d1);

	tr = new Transform2D();
	
	rect = new Rectangle2D(Point2D(0,0), DrawingWindow::width, DrawingWindow::height * 5);						
	player = new Rectangle2D(Point2D(DrawingWindow::width/2 - 50, DrawingWindow::height/2 - 50), 100, 100);		//


	enemy[1] = new  Rectangle2D(Point2D(50, 50), 100, 100);
	enemy[2] = new  Rectangle2D(Point2D(150, 150), 100, 100);
	enemy[3] = new  Rectangle2D(Point2D(700, 150), 100, 100);
	enemy[4] = new  Rectangle2D(Point2D(850, 50), 100, 100);

	healthbar[0] = new Rectangle2D(Point2D(DrawingWindow::width - 70, DrawingWindow::height - 110), 50, 50);

	healthbar[1] = new Rectangle2D(Point2D(DrawingWindow::width - 130, DrawingWindow::height - 110), 50, 50);

	healthbar[2] = new Rectangle2D(Point2D(DrawingWindow::width - 190, DrawingWindow::height - 110), 50, 50);

	gameover = new Rectangle2D(Point2D(0,0), DrawingWindow::width, DrawingWindow::height);

	effect =  new Rectangle2D(Point2D(-200, -250), 100, 100);

	// Gloante:
	for(int i=0; i<10; i++) 
	{
	bullet[i] = new Rectangle2D(Point2D(500,200),100,100);
	bullet[i]->color = Color(255,255,255);
	bullet[i]->fill = true;
	}
	
	tr->loadIdentityMatrix();
	tr->scaleMatrix(0.075, 0.15);
	tr->translateMatrix(-0.01, -0.007);
	tr->applyTransformTextures(effect);

	addObject2D(bullet[0]);
	addObject2D(healthbar[0]);
	addObject2D(healthbar[1]);
	addObject2D(healthbar[2]);
	addObject2D(enemy[1]);
	addObject2D(enemy[2]);
	addObject2D(enemy[3]);
	addObject2D(enemy[4]);
	
	addObject2D(effect);
	addObject2D(player);																						
	addObject2D(rect);

	addTextures();
	text[0] = new Text("lifes remaining:", Point2D(DrawingWindow::width - 170, DrawingWindow::height - 40), Color(255, 255 ,255), GLUT_BITMAP_TIMES_ROMAN_24);
	addText(text[0]);

	text[1] = new Text("Score:", Point2D(30, DrawingWindow::height - 40), Color(255, 255 ,255), GLUT_BITMAP_TIMES_ROMAN_24);
	addText(text[1]);

	text[1] = new Text(itoa(score, score_buffer,10), Point2D(120, DrawingWindow::height - 40), Color(255, 255 ,255), GLUT_BITMAP_TIMES_ROMAN_24);
	addText(text[1]);
}

void processKeys() {

	if((move_keys & 1) == 1)
	{

				tr->loadIdentityMatrix();
				tr->translateMatrix(3 * sin(player->angle) , 3 * cos(player->angle));
				tr->applyTransform_o(player);
	}
	if( ((move_keys & 1) == 1) && (((move_keys & 8) >> 3) == 1) ) 
	{
		// Up
				tr->loadIdentityMatrix();
				tr->translateMatrix(6 * sin(player->angle) , 6 * cos(player->angle));
				tr->applyTransform_o(player);
	}

	if(((move_keys & 2) >> 1) == 1) {
		// Left	
		tr->loadIdentityMatrix();
		tr->rotateSingleObject(player, 0.034906585f);
		player->angle = player->angle - 0.034906585f;

		if(player->angle < 0) {
			player->angle = 2 * PI - player->angle;
		}
	}

	if(((move_keys & 4) >> 2) == 1) {
		// Leftm
		tr->loadIdentityMatrix();
		tr->rotateSingleObject(player, 6.248278722f);
		player->angle = player->angle + 0.034906585f;

		if(player->angle >= 2 * PI) {
			player->angle = player->angle - 2 * PI;
		}
	}			
}

bool isOnMap(Point2D *p)
{
	if( ((p->x - 40 >= 0) && (p->x + 40 <= DrawingWindow::width )) && ((p->y - 40 >= 0) && (p->y + 40 <= DrawingWindow::height)) )
		return true;
	return false;
}

Point2D getCenter(Object2D *o) 
{
	int i;
	Point2D p;

	for(i=0; i<o->transf_points.size(); i++)
	{
		p.x = p.x + o->transf_points[i]->x;
		p.y = p.y + o->transf_points[i]->y;
	}

	p.x = p.x / o->transf_points.size();
	p.y = p.y / o->transf_points.size();
	return p;
}

void colisionDetection() 
{
	Point2D g[6];
	int i, j, aux = -3;

	// Obtin centrele de greutate de la obiecte:
	g[0] = getCenter(player);
	g[5] = getCenter(bullet[0]);

	for(i=1; i <= 4; i++)
	{
		if(enemy[i]->lock == false)
			g[i] = getCenter(enemy[i]);
		else 
		{
			g[i].x = -1000;
			g[i].y = -1000;
		}
	}
	
	// Verific daca au iesit de pe harta	
	// pt obiectul 1:
	for(i=0; i<= 4; i++)
	{
		if(!isOnMap(&g[i]))
		{
			// Muta jucatorul mai in spate dupa
			// coliziunea cu marginile
			tr->loadIdentityMatrix();
			if(g[i].x - 50 < 0)
			{
				tr->translateMatrix(50, 0);	
				if(i > 0)
					enemy[i]->angle = 2 * PI - PI/4;
			}
			if(g[i].x + 50 > DrawingWindow::width)
			{

				tr->translateMatrix(-50, 0);
				if(i > 0)
					enemy[i]->angle = PI / 2 - PI/4;
			}
			if(g[i].y - 50 < 0)
			{
				tr->translateMatrix(0, 50);
				if(i > 0)
					enemy[i]->angle =  PI/4;
			}
			if(g[i].y + 50 > DrawingWindow::height)
			{
				tr->translateMatrix(0, -50);
				if(i > 0)
					enemy[i]->angle = 5 * PI/4 ;
			}

			switch(i) {

				case 0: tr->applyTransform_o(player);
					break;

				default: tr->applyTransform_o(enemy[i]);
					break;
			}

			// Explodeaza si pierde o viata
			// daca jucatorul este 0
				if( i == 0)
				{
					affectLife(player);
				}
			}
		
		// Verific daca s-au ciocnit intre ele
		for(j=0; j<=5; j++)
		{
			if(i!= j)
			{
				if(aux != j)
				if(sqrt( (g[i].x - g[j].x) * (g[i].x - g[j].x) + (g[i].y - g[j].y) * (g[i].y - g[j].y) ) <= 100)
				{
					aux = i;

					// Daca se ciocneste player de una din navele inamicilor scad o viata:
					// si fac efectul de explozie
					if((i == 0) && (j != 5)) 
						affectLife(player);

					if((j == 5) && (i != 0))
						affectLife(enemy[i]);

					switch(i) {
						case 0: 
								if( j != 5 )
								{
									tr->loadIdentityMatrix();
									tr->translateMatrix(50 * sin(player->angle + PI), 50 * cos(player->angle + PI));
									tr->applyTransform_o(player);

									tr->loadIdentityMatrix();
									tr->translateMatrix(50 * sin(player->angle), 50 * cos(player->angle));

									if(j>0) 
									{
										tr->applyTransform_o(enemy[j]);
									}
								}
								break;

						default: 
								tr->loadIdentityMatrix();
								tr->translateMatrix(50 * sin(enemy[i]->angle + PI), 50 * cos(enemy[i]->angle + PI));
								enemy[i]->angle = enemy[i]->angle + PI;
								tr->applyTransform_o(enemy[i]);	

								tr->loadIdentityMatrix();
								tr->translateMatrix(50 * sin(enemy[i]->angle), 50 * cos(enemy[i]->angle));
								if((j>0) && ( j != 5))
								{
									tr->applyTransform_o(enemy[j]);
									enemy[j]->angle = enemy[j]->angle + PI;
								}
								break;
						}
					
				}
			}

		}

	}
}

void effectsAnimation() {
	// Explosion effect:
	if(frames > 16)
	{
			tr->loadIdentityMatrix();
			tr->translateMatrix(-1000,-1000);
			tr->applyTransform_o(effect);

			tr->loadIdentityMatrix();
			tr->translateMatrix(-1,0);
			tr->applyTransformTextures(effect);
			frames = frames ^ frames;
			explosion_effect = false;
	
	}
	else
	{
		if((split_frames & 32) == 32)
		{
			tr->loadIdentityMatrix();
			tr->translateMatrix(0.0625f,0);
			tr->applyTransformTextures(effect);
			split_frames = split_frames >> 5;
			frames++;
		}
			split_frames = split_frames << 1;
	}
}

void onFire() 
{
	if(bullet[0]->lock == false)
	{
		// copiez coordonatele:
		tr->setTheNewG(player, bullet[0]);
		bullet[0]->lock = true;
		bullet[0]->angle = player->angle;
	}
	else
	{
		if(isOnMap(&getCenter(bullet[0])) == false)
			bullet[0]->lock = false;
		tr->loadIdentityMatrix();
		tr->translateMatrix(10 * sin(bullet[0]->angle), 10 * cos(bullet[0]->angle));
		tr->applyTransform_o(bullet[0]);
	}

}

void DrawingWindow::onIdle()
{
	tr->loadIdentityMatrix();
	tr->translateMatrix(0, -0.1f);
	tr->applyTransform_o(rect);

	if(explosion_effect == true) 
		effectsAnimation();

	onFire();
	moveEnemy();
	processKeys();
	colisionDetection();
}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width,int height)
{
	v2d1->poarta(0,0,width,height); 
}


void DrawingWindow::onSpecialKeyUp(int key)
{
	switch(key)
	{
		case GLUT_KEY_UP:	{
				move_keys = move_keys & (~1);
				cout<<"Up released\n";
			    }
				break;

		case GLUT_KEY_LEFT: {
				move_keys = move_keys & (~2) ;
				cout<<"Left released\n";
				}
				break;

		case GLUT_KEY_RIGHT: {
				move_keys = move_keys & (~4) ;
				cout<<"Right released\n";
				}
				break;

	}
}


//functia care defineste ce se intampla cand se apasa pe tastatura
void DrawingWindow::onSpecialKey(int key)
{
	switch(key)
	{
	case GLUT_KEY_UP:	move_keys = move_keys | 1 ;
			break;

	case GLUT_KEY_LEFT: move_keys = move_keys | 2 ;
			break;

	case GLUT_KEY_RIGHT: move_keys = move_keys | 4 ;
			break;

	case 27 : exit(0);
			break;
	}
}


void DrawingWindow::onKey(unsigned char key)
{
	switch(key) {

	case '/':	move_keys = move_keys | 8 ;
		break;
	}
}


void DrawingWindow::onKeyUp(unsigned char key)
{
	switch(key) {

	case '/':	move_keys = move_keys & (~8) ;
		break;
	}
}


//functia care defineste ce se intampla cand se da click pe mouse
void DrawingWindow::onMouse(int button,int state,int x, int y)
{
	
}


int main(int argc, char** argv)
{
	//creare fereastra
	DrawingWindow dw(argc, argv, 1024, 768, 200, 100, "Laborator EGC");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}