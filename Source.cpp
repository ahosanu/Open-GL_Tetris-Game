#include<windows.h>
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glaux.lib")

#include <GL/glut.h>
#include <GL/GLAux.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <ctime>
#include <string> 
using namespace std;

#define PI 3.1416
static GLfloat spin = 0.0;//initial degree for spinning
static GLfloat spin2 = 0.0;//initial degree for spinning
int px=6, py=0, pz=0;
int cr = 25, cg=100, cb=55, s=0,nr = 23,ng=30 , nb=140, i = 0, nextM = 0, Score = 0, max_x, HighSchore = 0;
int nextMR, nextMG, nextMB, present, GameStage = 1;
float tpX = 0, tpY = 0;
bool GameRun = true;


//=====================================================================================

typedef struct list{
	int cr, cg, cb;
	int rect[4][4];
} Box;
typedef struct lists{
	int cr, cg, cb;
} MianBox;
MianBox FullWin[20][20];
Box Winbox[22];

void iShowBMP(int x, int y, char filename[])
{
	
	AUX_RGBImageRec *TextureImage;

	TextureImage = auxDIBImageLoad(filename);

	glRasterPos2f(x, y);
	glDrawPixels(TextureImage->sizeX, TextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);

	free(TextureImage->data);
	free(TextureImage);
	
}
void output(int x, int y, float r, float g, float b, void *font, char *string)
{
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
}
void rect(int x,int y){
	
	glPushMatrix();
		glTranslated(x,y,0);
		glBegin(GL_QUADS);
			glVertex2d(.1, .1);
			glVertex2d(.1, 2);
			glVertex2d(2, 2);
			glVertex2d(2, .1);
		glEnd();
	glPopMatrix();
}
void mkbox(int arr[4][4]){

	for (int i = 0, y=38; i < 4; i++,y-=2){
		for (int j = 0,x=10; j < 4-i; j++,x+=2){
			if (arr[i][j] == 1){
				rect(x, y);
			}
		}
	}
}
void liney(double width, double x1, double y1, double x2, double y2){
	glBegin(GL_QUADS);
		glVertex2d(x1, y1);
		glVertex2d(x1, y1 + width);
		glVertex2d(x2, y2 + width);
		glVertex2d(x2, y2);
	glEnd();
}
void linex(double width, double x1, double y1, double x2, double y2){
	glBegin(GL_QUADS);
	
	glVertex2d(x1, y1);
	glVertex2d(x1+width, y1);
	glVertex2d(x2+width, y2);
	glVertex2d(x2, y2);
	glEnd();
}
void Drow_Object(int x, int y){
	glPushMatrix();
		glColor3d((double)nr / 255, (double)ng / 255, (double)nb / 255);
		glTranslated(x, y, 0);
		glPushMatrix();
			mkbox(Winbox[s].rect);
		glPopMatrix();
	glPopMatrix();
}
void Drow_Full_Fill_box(){
	glPushMatrix();
	for (int i = 0, gy = 0; i < 20; i++, gy += 2){
		for (int j = 0, gx = 0; j < 20; j++, gx += 2){
			if (FullWin[i][j].cb > 0 || FullWin[i][j].cr > 0){
				glPushMatrix();
				glColor3d((double)FullWin[i][j].cr / 255, (double)FullWin[i][j].cg / 255, (double)FullWin[i][j].cb / 255);
				rect(gx, gy);
				glPopMatrix();
			}
		}
	}
	glPopMatrix();
}
void DrowGrid(){
	glColor3d((double)22 / 256, (double)150 / 256, (double)122 / 256);
	liney(1, 0, 40, 40, 40);
	linex(1, 40, 0, 40, 41);
	glColor3d((double)22 / 256, (double)22 / 256, (double)22 / 256);
	for (int i = 40; i > 0; i -= 2){
		liney(.1, 0, i, 40, i);
	}
	for (int i = 2; i < 40; i += 2){
		linex(.1, i, 0, i, 40);
	}
}
bool chackMove(){
	if (s == 0 && px + 2 <= 22){
		return true;
	}
	else if (s == 1 && px + 2 <= 28){
		return true;
	}
	else if (s == 2 && px + 2 <= 28){
		return true;
	}
	else if (s == 3 && px + 2 <= 26){
		return true;
	}
	else if (s == 4 && px + 2 <= 28){
		return true;
	}
	else if (s == 5 && px + 2 <= 24){
		return true;
	}
	else if (s == 6 && px + 2 <= 28){
		return true;
	}
	else if (s == 7 && px + 2 <= 24){
		return true;
	}
	else if (s == 8 && px + 2 <= 26){
		return true;
	}
	else if (s == 9 && px + 2 <= 24){
		return true;
	}
	else if (s == 10 && px + 2 <= 26){
		return true;
	}
	else if (s == 11 && px + 2 <= 24){
		return true;
	}
	else if (s == 12 && px + 2 <= 26){
		return true;
	}
	else if (s == 13 && px + 2 <= 24){
		return true;
	}
	else if (s == 14 && px + 2 <= 26){
		return true;
	}
	else if (s == 15 && px + 2 <= 24){
		return true;
	}
	else if (s == 16 && px + 2 <= 26){
		return true;
	}
	else if (s == 17 && px + 2 <= 24){
		return true;
	}
	else if (s == 18 && px + 2 <= 26){
		return true;
	}
	else if (s == 19 && px + 2 <= 26){
		return true;
	}
	else if (s == 20 && px + 2 <= 24){
		return true;
	}
	else if (s == 21 && px + 2 <= 26){
		return true;
	}

	return false;
}
bool chack(){
	int NewpointY, max_y = py;
	max_x = px;
	int NewpointX;
	for (int i = 0, pointY = py; i < 4; i++, pointY -= 2){
		for (int j = 0, pointX = px; j < 4 - i; j++, pointX += 2){

			

			if (Winbox[s].rect[i][j] == 1){
				NewpointY = (38 + pointY) / 2;
				NewpointX = (10 + pointX) / 2;
				max_y = (38 + pointY);
				max_x = (10 + pointX);
				if (FullWin[NewpointY-1][NewpointX].cb > 0 || FullWin[NewpointY-1][NewpointX].cg > 0 || FullWin[NewpointY-1][NewpointX].cr > 0)
					return false;
			}
		}
		if (max_y <= 0)
			return false;
	
	}
	return true;
}
bool chackRight(){

	int NewpointY, max_y = py;
	max_x = px;
	int NewpointX;
	for (int i = 0, pointY = py; i < 4; i++, pointY -= 2){
		for (int j = 0, pointX = px; j < 4 - i; j++, pointX += 2){

			if (Winbox[s].rect[i][j] == 1){
				NewpointY = (38 + pointY) / 2;
				NewpointX = (10 + pointX) / 2;
				max_y = (38 + pointY);
				max_x = (10 + pointX);
				if (FullWin[NewpointY][NewpointX + 1].cb > 0 || FullWin[NewpointY][NewpointX + 1].cg > 0 || FullWin[NewpointY][NewpointX + 1].cr > 0)
					return false;
			}
		}
		if (max_y <= 0)
			return false;
		if (max_x >= 38)
			return false;

	}
	return true;
}
bool chackLeft(){

	int NewpointY, max_y = py;
	max_x = px;
	int NewpointX;
	for (int i = 0, pointY = py; i < 4; i++, pointY -= 2){
		for (int j = 0, pointX = px; j < 4 - i; j++, pointX += 2){

			if (Winbox[s].rect[i][j] == 1){
				NewpointY = (38 + pointY) / 2;
				NewpointX = (10 + pointX) / 2;
				max_y = (38 + pointY);
				max_x = (10 + pointX);
				if (FullWin[NewpointY][NewpointX - 1].cb > 0 || FullWin[NewpointY][NewpointX - 1].cg > 0 || FullWin[NewpointY][NewpointX - 1].cr > 0)
					return false;
			}
		}
		if (max_y <= 0)
			return false;

	}
	return true;
}
void display(void)
{

	//cout << px << endl;
	glClear(GL_COLOR_BUFFER_BIT);
	//cout << px << " | " << py << " | " << s << endl;
	if (GameStage == 1){
		iShowBMP(0, 0, "main.bmp");
	}
	else if (GameStage == 2){
		iShowBMP(0, 0, "instruction.bmp");
	}
	else if (GameStage == 4){
		iShowBMP(0, 0, "about.bmp");
	}
	else if (GameStage == 3){

		//corner Part
		glPushMatrix();
		glColor3d(1, 1, 1);
		glBegin(GL_POLYGON);
		glVertex2d(40, 40);
		glVertex2d(0, 40);
		glVertex2d(0, 50 - .1);
		glVertex2d(52.5, 50 - .1);
		glVertex2d(52.5, 0);
		glVertex2d(40, 0);
		glEnd();
		glPopMatrix();
		//End Corner Part


		//Your Score Text
		output(2, 47, 1, 0, 1, GLUT_BITMAP_9_BY_15, "Your Score");
		string sc = to_string(Score);
		int i = 0;
		char scr[10];
		while (sc[i]){
			scr[i] = sc[i];
			//			cout << sc[i];
			i++;
		}
		scr[i] = '\0';
		output(2, 45, 1, 0, 1, GLUT_BITMAP_HELVETICA_18, scr);
		//End Your Score Text


		//High Score
		output(19, 47, 1, 0, 1, GLUT_BITMAP_9_BY_15, "Your High Score");
		sc = to_string(HighSchore);
		i = 0;
		scr[10];
		while (sc[i]){
			scr[i] = sc[i];
			i++;
		}
		scr[i] = '\0';
		output(19, 45, 1, 0, 1, GLUT_BITMAP_HELVETICA_18, scr);
		//End High Score


		//Present Object 
		glColor3d(1, 0, 0);
		output(42.5, 35.5, 1, 0, 1, GLUT_BITMAP_9_BY_15, "Presenr");
		//Drow Present Object 
		glPushMatrix();
		glColor3d((double)nr / 255, (double)ng / 255, (double)nb / 255);
		glTranslated(33, -8, 0);
		glPushMatrix();
		mkbox(Winbox[present].rect); //drow rect
		glPopMatrix();
		glPopMatrix();
		//End Present Object 


		//Next Object 
		output(44, 18.5, 1, 0, 1, GLUT_BITMAP_9_BY_15, "Next");
		//cout << tpX << " | " << tpY << endl;
		//Drow Object
		glPushMatrix();
		glColor3d((double)nextMR / 255, (double)nextMG / 255, (double)nextMB / 255);
		glTranslated(33, -27, 0);
		glPushMatrix();
		mkbox(Winbox[nextM].rect);
		glPopMatrix();
		glPopMatrix();
		//End Next Object 


		if (GameRun){
			glPushMatrix();
			DrowGrid();
			Drow_Object(px, py);
			Drow_Full_Fill_box();
			glPopMatrix();
		}
		else{
			iShowBMP(0, 0, "gameOver.bmp");
		}

		iShowBMP(46, 45, "gameReload.bmp");
		iShowBMP(40, 45, "gameBack.bmp");
	}

	glFlush();
}
bool chackRot(int x){
	int NewpointY, max_y = py;
	int newmax_x = px;
	int NewpointX;
	for (int i = 0, pointY = py; i < 4; i++, pointY -= 2){
		for (int j = 0, pointX = px; j < 4 - i; j++, pointX += 2){



			if (Winbox[x].rect[i][j] == 1){
				NewpointY = (38 + pointY) / 2;
				NewpointX = (10 + pointX) / 2;
				max_y = (38 + pointY);
				newmax_x = (10 + pointX);
				if (FullWin[NewpointY][NewpointX].cb > 0 || FullWin[NewpointY][NewpointX].cg > 0 || FullWin[NewpointY][NewpointX].cr > 0)
					return false;
			}
		}
		if (max_y <= 0)
			return false;
		if (newmax_x > 38)
			return false;

	}
	return true;
}
void obj_rot(){
	if (s == 21){
		if (chackRot(s-1))
			s--;
	}
	else if (s == 20){
		if (chackRot(s + 1))
			s++;
	}
	else if (s == 0){
		if (chackRot(s + 1))
		s++;
	}
	else if (s == 1){
		if (chackRot(s + 1))
		s--;
	}
	else if (s == 3){
		if (chackRot(s + 1))
		s++;
	}
	else if (s == 4){
		if (chackRot(s + 1))
		s--;
	}
	else if (s == 5){
		if (chackRot(s + 1))
		s++;
	}
	else if (s == 6){
		if (chackRot(s - 1))
		s--;
	}
	else if (s == 7){
		if (chackRot(s + 1))
		s++;
	}
	else if (s == 8){
		if (chackRot(s + 1))
		s++;
	}
	else if (s == 9){
		if (chackRot(s + 1))
		s++;
	}
	else if (s == 10){
		if (chackRot(7))
		s=7;
	}
	else if (s == 11){
		if (chackRot(s + 1))
		s++;
	}
	else if (s == 12){
		if (chackRot(s + 1))
		s++;
	}
	else if (s == 13){
		if (chackRot(s + 1))
		s++;
	}
	else if (s == 14){
		if (chackRot(11))
		s = 11;
	}
	else if (s == 15){
		if (chackRot(s + 1))
		s++;
	}
	else if (s == 16){
		if (chackRot(s + 1))
		s++;
	}
	else if (s == 17){
		if (chackRot(s + 1))
		s++;
	}
	else if (s == 18){
		if (chackRot(15))
		s = 15;
	}

}
void init(void)
{
	glClearColor((double)0 / 255, (double)0 / 255, (double)0 / 255, 0.0);
	glOrtho(0, 52.5, 0, 50, -50.0, 50.0);

	nr = rand() % 255;
	srand(time(NULL));
	present  = s = rand() % 22;
	nextMR = rand() % 255;
	nextMG = rand() % 255;
	nextMB = rand() % 255;

	nextM = rand() % 22;
	//s = 19;
	//II
	Winbox[0].rect[0][0] = 1;
	Winbox[0].rect[0][1] = 1;
	Winbox[0].rect[0][2] = 1;
	Winbox[0].rect[0][3] = 1;

	//II
	Winbox[1].rect[0][0] = 1;
	Winbox[1].rect[1][0] = 1;
	Winbox[1].rect[2][0] = 1;
	Winbox[1].rect[3][0] = 1;

	//.
	Winbox[2].rect[0][0] = 1;

	//i
	Winbox[3].rect[0][0] = 1;
	Winbox[3].rect[0][1] = 1;

	//i
	Winbox[4].rect[0][0] = 1;
	Winbox[4].rect[1][0] = 1;



	//I
	Winbox[5].rect[0][0] = 1;
	Winbox[5].rect[0][1] = 1;
	Winbox[5].rect[0][2] = 1;

	//I
	Winbox[6].rect[0][0] = 1;
	Winbox[6].rect[1][0] = 1;
	Winbox[6].rect[2][0] = 1;


	//T
	Winbox[7].rect[0][0] = 1;
	Winbox[7].rect[0][1] = 1;
	Winbox[7].rect[0][2] = 1;
	Winbox[7].rect[1][1] = 1;

	//T
	Winbox[8].rect[1][0] = 1;
	Winbox[8].rect[0][1] = 1;
	Winbox[8].rect[1][1] = 1;
	Winbox[8].rect[2][1] = 1;

	//T
	Winbox[9].rect[0][1] = 1;
	Winbox[9].rect[1][0] = 1;
	Winbox[9].rect[1][1] = 1;
	Winbox[9].rect[1][2] = 1;

	//T
	Winbox[10].rect[1][1] = 1;
	Winbox[10].rect[0][0] = 1;
	Winbox[10].rect[1][0] = 1;
	Winbox[10].rect[2][0] = 1;

	//L
	Winbox[11].rect[1][2] = 1;
	Winbox[11].rect[0][0] = 1;
	Winbox[11].rect[0][1] = 1;
	Winbox[11].rect[0][2] = 1;

	//L
	Winbox[12].rect[2][0] = 1;
	Winbox[12].rect[0][1] = 1;
	Winbox[12].rect[1][1] = 1;
	Winbox[12].rect[2][1] = 1;

	//L 
	Winbox[13].rect[0][0] = 1;
	Winbox[13].rect[1][0] = 1;
	Winbox[13].rect[1][1] = 1;
	Winbox[13].rect[1][2] = 1;

	//L 
	Winbox[14].rect[0][1] = 1;
	Winbox[14].rect[0][0] = 1;
	Winbox[14].rect[1][0] = 1;
	Winbox[14].rect[2][0] = 1;

	//L 
	Winbox[15].rect[1][0] = 1;
	Winbox[15].rect[0][0] = 1;
	Winbox[15].rect[0][1] = 1;
	Winbox[15].rect[0][2] = 1;

	//L 
	Winbox[16].rect[0][0] = 1;
	Winbox[16].rect[0][1] = 1;
	Winbox[16].rect[1][1] = 1;
	Winbox[16].rect[2][1] = 1;


	//L 
	Winbox[17].rect[0][2] = 1;
	Winbox[17].rect[1][0] = 1;
	Winbox[17].rect[1][1] = 1;
	Winbox[17].rect[1][2] = 1;

	//L 
	Winbox[18].rect[2][1] = 1;
	Winbox[18].rect[0][0] = 1;
	Winbox[18].rect[1][0] = 1;
	Winbox[18].rect[2][0] = 1;


	//O
	Winbox[19].rect[0][0] = 1;
	Winbox[19].rect[0][1] = 1;
	Winbox[19].rect[1][0] = 1;
	Winbox[19].rect[1][1] = 1;

	//Z
	Winbox[20].rect[0][0] = 1;
	Winbox[20].rect[0][1] = 1;
	Winbox[20].rect[1][1] = 1;
	Winbox[20].rect[1][2] = 1;
	
	//Z
	Winbox[21].rect[0][1] = 1;
	Winbox[21].rect[1][1] = 1;
	Winbox[21].rect[1][0] = 1;
	Winbox[21].rect[2][0] = 1;

}
void my_keyboard(unsigned char key, int x, int y)
{

	switch (key) {

	case 'r':
		obj_rot();
		glutPostRedisplay();
		break;

	case 'w':
		tpY += .5;
		glutPostRedisplay();
		break;

	case 's':
		tpY -= .5;
		glutPostRedisplay();
		break;

	case 'a':
		tpX -= .5;
		glutPostRedisplay();
		break;
	case 'd':
		tpX += .5;
		glutPostRedisplay();
		break;

	default:
		//glutIdleFunc(NULL);
		break;
	}
}
void spe_key(int key, int x, int y)
{

	switch (key) {

	case GLUT_KEY_LEFT:
		if (chackLeft() && px - 2 >= -10 && GameRun){
			px -= 2;
			glutPostRedisplay();
		}
		break;

	case GLUT_KEY_RIGHT:
		if (max_x + 2 <= 38 && chackRight() && GameRun){
			px += 2;
			glutPostRedisplay();
		}
		break;

	case GLUT_KEY_DOWN:
		if (chack() && GameRun){
			py -= 2;
			glutPostRedisplay();
		}
		break;

	case GLUT_KEY_UP:

		//py += 2;
		//glutPostRedisplay();
		break;
	default:
		break;
	}
}

void LoadBox(){
	
	for (int i = 0, pointY = py; i < 4; i++,pointY-=2){
		for (int j = 0, pointX = px; j < 4 - i; j++, pointX+=2){
			if (Winbox[s].rect[i][j] == 1){
				int NewpointY = (38 + pointY)/2;
				int NewpointX = (10 + pointX)/2;
				FullWin[NewpointY][NewpointX].cb = nb;
				FullWin[NewpointY][NewpointX].cr = nr;
				FullWin[NewpointY][NewpointX].cg = ng;
			}
		}
	}
}
void removeLine(){
	int count = 0;
	

	while (true){
		int t = 0;
		count = 0;
		for (; t < 20; t++){
			for (int j = 0; j < 20; j++){
				if (FullWin[t][j].cb > 0 || FullWin[t][j].cg > 0 || FullWin[t][j].cr > 0)
					count++;
			}
			if (count >= 20)
				break;
			count = 0;
		}
		if (count >= 20){
			for (int i = t; i < 19; i++){
				for (int j = 0; j < 20; j++){
					FullWin[i][j].cb = FullWin[i + 1][j].cb;
					FullWin[i][j].cr = FullWin[i + 1][j].cr;
					FullWin[i][j].cg = FullWin[i + 1][j].cg;
				}
			}
		}
		else{
			break;
		}
	}

}
bool GameOver(){
	for (int j = 0; j < 20; j++){
		if (FullWin[19][j].cb > 0 || FullWin[19][j].cg > 0 || FullWin[19][j].cr > 0)
			return true;
	}
	return false;
}
void autoLoad(){
	
	if (i > 5000000 && chack()){
		py -= 2;
		i = 0;
		glutPostRedisplay();
	}
	if (!chack()){
		
		LoadBox();
		removeLine();
		if (GameOver()){
			if (HighSchore < Score)
				HighSchore = Score;
			GameRun = false;
			glutPostRedisplay();
		}
		if (GameRun){
			Score += 5;
			py = 0;
			px = 6;
			nr = nextMR;
			ng = nextMG;
			nb = nextMB;
			present = s = nextM;

			nextMR = rand() % 255;
			nextMG = rand() % 255;
			nextMB = rand() % 255;

			nextM = rand() % 22;
		}
	}
	i++;
}
void Mous_click(int key, int state, int x, int y){

	//cout << x << " | " << y << endl;
	if (GameStage == 1){
		if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			if (x >= 140 && x <= 292 && y >= 229 && y <= 262){
				glutIdleFunc(autoLoad);
				GameRun = true;
				GameStage = 3; //Playing
				glutPostRedisplay();
			}
			else if (x >= 209 && x <= 362 && y >= 302 && y <= 337){
				GameStage = 2; // Instruction 
				glutPostRedisplay();
			}
			else if (x >= 262 && x <= 411 && y >= 367 && y <= 398){
				GameStage = 4; // About 
				glutPostRedisplay();
			}

		}

	}
	else if (GameStage == 2 || GameStage == 4){
		if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			if (x >= 19 && x <= 81 && y >= 15 && y <= 76){
				GameStage = 1;
				glutPostRedisplay();
			}

		}

	}else if (GameStage == 3){
		if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			if (x >= 323 && x <= 354 && y >= 16 && y <= 45){
				//Back When Playing 
				GameRun = false;
				glutIdleFunc(NULL);
				GameStage = 1;
				GameRun = true;
				Score = 0;
				py = 0;
				px = 6;
				nr = rand() % 255;
				ng = rand() % 255;
				nb = rand() % 255;
				present = s = rand() % 22;

				nextMR = rand() % 255;
				nextMG = rand() % 255;
				nextMB = rand() % 255;

				nextM = rand() % 22;

				for (int i = 0; i < 20; i++){
					for (int j = 0; j < 20; j++){
						FullWin[i][j].cr = 0;
						FullWin[i][j].cg = 0;
						FullWin[i][j].cb = 0;
					}
				}
			}

			if (x >= 371 && x <= 400 && y >= 15 && y <= 44){
				GameRun = true;
				Score = 0;
				py = 0;
				px = 6;
				nr = rand() % 255;
				ng = rand() % 255;
				nb = rand() % 255;
				present = s = rand() % 22;

				nextMR = rand() % 255;
				nextMG = rand() % 255;
				nextMB = rand() % 255;

				nextM = rand() % 22;

				for (int i = 0; i < 20; i++){
					for (int j = 0; j < 20; j++){
						FullWin[i][j].cr = 0;
						FullWin[i][j].cg = 0;
						FullWin[i][j].cb = 0;
					}
				}
			}
			glutPostRedisplay();
		}
	}

}
int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(420, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Tetris");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(my_keyboard);
	glutMouseFunc(Mous_click);
	glutSpecialFunc(spe_key);//up,down,left,right
	
	glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}

