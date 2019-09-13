#include<windows.h>
//#include<fstream>
#include<stdlib.h>
#include<GL/glut.h>
#include<stdio.h>
#include<time.h>
/*#include<iostream>
using namespace std;
ifstream fin;
ofstream fout;*/
float speed=0.04;
float block1x=50.0,block1y=0,heli=0.0,mnk=1;
int i=0,ijk=0,flg=1;
char str1[20];
clock_t begin_time ;
int flag=0;
void init(void)
{
	block1y=(rand()%45)+10;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0 , 0.0);
}
void drawcopter()
{
	glColor3f(0.8,0.498039,0.196078);
	glRectf(10,49.8,19.8,44.8);
	glRectf(2,46,10,48);
	glRectf(2,46,4,51);
	glRectf(14,49.8,15.8,52.2);
	glRectf(7,53.6,22.8,52.2);
}
void renderBitmapString(float x,float y,float z,void *font,char *string)
{
	char *c;
	glRasterPos3f(x,y,z);
	for (c=string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}
float getscore(float x)
{
    float score=0.0,i,k;
    i=x;
    if(i<=10)
    {
        score+=10*i;

    }
    else if (i<=30)
    {
        score+=10*10+(i-10)*15;
    }
    else if(i<=90)
        score+=10*10+20*15+(i-30)*20;
    else

        score+=10*10+20*15+60*20+(i-90)*25;
        return score;
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	if( (i==360||i==-350)||(((int)block1x==10||(int)block1x==7||(int)block1x==4||(int)block1x==1)   &&(int)block1y<53+(int)heli&&(int)block1y+35>53+(int)heli)||(((int)block1x==9||(int)block1x==3||(int)block1x==6)&&(int)block1y<45+(int)heli&&(int)block1y+35>45+(int)heli) ||(((int)block1x==0)&&(int)block1y<46+(int)heli&&(int)block1y+35>46+(int)heli))
	{
		glColor3f(0.8,0.498039,0.196078);
		glRectf(0.0,0.0,100.0,100.0);
		glColor3f(0.0,0.0,0.0);
        renderBitmapString(10,70,0,GLUT_BITMAP_TIMES_ROMAN_24,"\n******GAME OVER******\n");
        renderBitmapString(70,58,0,GLUT_BITMAP_TIMES_ROMAN_24,str1);

		glutSwapBuffers();
		glFlush();
        printf("\n*********GAME OVER***********\n");
        for(int j=0;j<50000;j++)
        for(int k=0;k<5000;k++);
        printf("\nStart New Game\n");

        float t=float( clock () - begin_time ) /  CLOCKS_PER_SEC;
        float score=getscore(t);
        printf("score=%f\n",score);

        /*fin.open("D:\cgprog\HelicopterGame\score.txt");

        fout.open("D:\cgprog\HelicopterGame\source.txt");
        float high=0;
        //fin>>high;
        //cout<<high;
        if(high<score)
        {
            printf("!!!!!!!!!!NEW HIGH SCORE!!!!!!!!!!");
            fout<<score;
        }
        else printf("HIGH SCORE=%f",high);*/
        exit(0);
	}
	else if(flg==1)
	{
		flg=0;
		glColor3f(0.3,0.7,0.2);
		printf("\n------------------------------------------------------------------\n");
		printf("Steps to run this cg project\n");
		printf("\n------------------------------------------------------------------\n");
		printf("Step1: Click any mouse key to start\n");
		printf("\nStep2: Click and hold left mouse key to handle the helicopter\n\n");
		drawcopter();
		glutSwapBuffers();
		glFlush();
	}
	else
	{
		glPushMatrix();
		glColor3f(0.90,0.91,0.98);
		glRectf(0.0,100.0,100.0,10.0);
		glRectf(0.0,50.0,100.0,40.0);
		ijk=(int)mnk;
		renderBitmapString(20,3,0,GLUT_BITMAP_TIMES_ROMAN_24,str1);
		glTranslatef(0.0,heli,0.0);
		drawcopter();
		if(block1x<-10)
		{
			block1x=50;
			block1y=(rand()%16)+20;
		}
		else block1x-=speed;
		glTranslatef(block1x,-heli,0.0);
		glColor3f(0.0,0.0,0.0);
		glRectf(block1x,block1y,block1x+3,block1y+30);
		glPopMatrix();
		glutSwapBuffers();
		glFlush();
	}
}
void Heliup()
{
	heli+=0.1;
	i++;
	for(int j=0;j<5000;j++)
	for(int k=0;k<500;k++);
	glutPostRedisplay();
}
void Helidown()
{
	heli-=0.1;
	i--;
	for(int j=0;j<5000;j++)
	for(int k=0;k<500;k++);
	glutPostRedisplay();
}
void Reshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w<=h)
		glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,2.0*(GLfloat)h/(GLfloat)w,-10.0,20.0);
	else
		glOrtho(-2.0*(GLfloat)w/(GLfloat)h,2.0*(GLfloat)w/(GLfloat)h,-2.0,2.0,-10.0,20.0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
void mouse(int btn,int state,int x,int y)
{
    if(flag==0)
    {
        flag=1;
         begin_time = clock();

    }
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		glutIdleFunc(Heliup);
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
		glutIdleFunc(Helidown);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (500, 400);
	glutInitWindowPosition (200,300);
	glutCreateWindow (" The Helicopter Game");
	init();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMainLoop();
}
