#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <GL/glu.h>
#include <GL/GLAux.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "imageloader.h"
using namespace std;

#define pb push_back

int hBar = 0 ;
int hBall = 0 , vBall = -194 ;
int flag = 1 ;
bool flag2 = true ;
int state1 =0 , state2 =0;
int xIncr = 7 ;
int yIncr = 7 ;
int h=0 , v=0 , x , i=0;
int scanningFlag = 1;
int startingState = 1;
int fileNum = 1;
int score = 0;
char score_string[50];
char life_string[2];
int life = 3;
int state3=0;
float cubeX = 0.5;
float cubeY = 0.5;
int questionNumber ;
float cubeZ = 0.5;
bool vis[15],viss[22];
bool finishState = false;
bool charactersFlag = true;
bool getNewQuestion = true;
void *currentfont;
char readingFile[150] = "D:\\Programming\\DX-Ball\\scan1.txt";
bool drawingCube = true;
char answerArr[20];
int answerChCount =0;
bool hellYea = false;
bool hellNo = false;
char correctAnswer[50];
bool barTex = true;
bool ball1Tex = false;
GLuint textures;
Image *images[7];
char readingAnswer[50];
char tab2[250];
int readingAnswerCounter =0;
vector <string> questions , answers;
bool keys[256];
char theAnswer[20];
bool gotRight = false;
bool gotWrong = false;
bool winningFlag = true;
bool go2NextLevel = false;
bool startCounter =false;
bool power1 = false;
bool power2 = false;
bool hotpower = true;
int powerCounter =0;
int endTimer = 0;
struct block
{
	int x1,y1,x2,y2,value,power;
	char character;
};
block arr[100];

GLuint loadTexture(Image* image)
{
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image->width, image->height,0,GL_RGB,GL_UNSIGNED_BYTE,image->pixels);
	return textureId;
}
void getAllPics()
{
    int imgCounter =0;
    for(imgCounter =0 ; imgCounter < 7; imgCounter++)
    {
        if(imgCounter == 0)
            images[imgCounter] = loadBMP("D:\\Programming\\DX-Ball\\Icons\\bar_converted.bmp");
        else if(imgCounter == 1)
            images[imgCounter] = loadBMP("D:\\Programming\\DX-Ball\\Icons\\ball.bmp");
        else if(imgCounter == 2)
            images[imgCounter] = loadBMP("D:\\Programming\\DX-Ball\\Icons\\brick1.bmp");
        else if(imgCounter == 3)
            images[imgCounter] = loadBMP("D:\\Programming\\DX-Ball\\Icons\\brick2.bmp");
        else if(imgCounter == 4)
            images[imgCounter] = loadBMP("D:\\Programming\\DX-Ball\\Icons\\brick3.bmp");
        else if(imgCounter == 5)
            images[imgCounter] = loadBMP("D:\\Programming\\DX-Ball\\Icons\\brick4.bmp");
        else
            images[imgCounter] = loadBMP("D:\\Programming\\DX-Ball\\Icons\\boards.bmp");
    }
}
int convert2String(int switchingState)
{
    int s , counter , l , j;
    int intArray[50];
    if(switchingState == 1)
    {
        s = score;
        counter = 0;
        if(s == 0)
        {
            score_string[0] = '0';
            return 1;
        }
        else
        {
            while(s>0)
            {
                intArray[counter] = s%10;
                counter++;
                s/=10;
            }
        }
        j=0;
        for(l=counter-1;l>=0;l--)
        {
            score_string[j]=intArray[l]+'0';
            j++;
        }
        return j;
    }
    else if(switchingState == 2)
    {
        s = life;
        counter = 0;
        if(s == 0)
        {
            life_string[0] = '0';
            return 1;
        }
        else
        {
            while(s>0)
            {
                intArray[counter] = s%10;
                counter++;
                s/=10;
            }
        }
        j=0;
        for(l=counter-1;l>=0;l--)
        {
            life_string[j]=intArray[l]+'0';
            j++;
        }
        return j;
    }
}

void question ()
{
    printf("%d\n",i);
	questions.pb("I get wet when drying. I get dirty when wiping. What am I?");
	answers.pb("towel");
	questions.pb("I can be cracked, made, told, and played. What am I?");
	answers.pb("joke");
	questions.pb(" like to twirl my body but keep my head up high. After I go in, everything becomes tight. What am I?");
	answers.pb("screw");
	questions.pb("I can fly but I have no wings. I can cry but I have no eyes. Wherever I go, darkness follows me. What am I?");
	answers.pb("cloud");
	questions.pb("I eat, I live, I breathe, I live, I drink, I die. What am I?");
	answers.pb("fire");
	questions.pb("The more you take of me, the more you leave behind. What am I?");
	answers.pb("footstep");
	questions.pb("I have a neck and no head, two arms but no hands. I'm with you to school, I'm with you to work. What am I?");
	answers.pb("shirt");
	questions.pb("I shrink smaller every time I take a bath. What am I?");
	answers.pb("soap");
	questions.pb("I am heavy forward, but backward I'm not. What am I?");
	answers.pb("ton");
	questions.pb("I will disappear every time you say my name. What am I?");
	answers.pb("silence");
	while ( 1 )
	{
	    srand(time(NULL));
		questionNumber = rand() % 10 ;
		if ( !vis [questionNumber] )
        {
            vis[questionNumber]=true;
			break ;
        }
	}
	tab2[0] = 0;
	correctAnswer[0] = 0;
	strcpy(tab2, questions[questionNumber].c_str());
	strcpy(theAnswer,answers[questionNumber].c_str());
	int len = answers[questionNumber].size() , ind;
	int charNumber =0;
	for (charNumber=0 ; charNumber<len ; charNumber++ )
	{
		while ( 1 )
		{
			ind = rand () % 18 ;
			if ( !viss[ind] && arr[ind].value!=0)
            {
                viss [ind]=true ;
				break ;
            }
		}
		arr[ind].character=answers[questionNumber][charNumber];
	}
}

char saveTheAnswer[20];
int saveAnswer=0;
void saveAns ()
{
    for ( int c=0 ; c<i ; c++)
    {
        if ( arr[c].character >='a' && arr[c].character<='z' )
        {
            saveTheAnswer[saveAnswer]=arr[c].character;
            arr[c].character='/0';
            saveAnswer++;
        }
    }
}
bool comp ( char readingAnswer[] , int rdInd , char theAnswer[] , int anInd)
{
    if ( rdInd != anInd )
        return false;
    for ( int c=0 ; c<rdInd ; c++ )
        if ( readingAnswer[c]!=theAnswer[c] )
            return false;
    return true ;
}
void changeFile ()
{
    string s="D:\\Programming\\DX-Ball\\scan" ;
    s+=fileNum+'0';
    s+=".txt";
    memset(readingFile,NULL,strlen(readingFile));
    strcpy(readingFile,s.data());
	return ;
}
void drawText(const char *text , int len , float x , float y)
{
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX,matrix);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2d(x,y);
    int c;
    for(c=0;c<len ;c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text[c]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_PROJECTION);
    glutPostRedisplay();
}
void myStyleInit()
{
    memset(vis,0,15);
    ShowCursor(false);
	glEnable(GL_TEXTURE_2D);
    glClearColor ( 0.0 , 0.0 , 0.0 , 0.0 ) ;
    glPointSize ( 20.0 ) ;
    glLoadIdentity();
    glMatrixMode ( GL_PROJECTION ) ;
    glLoadIdentity ( ) ;
    glOrtho (-400 , 400 , -300 , 300 , 0 , -1) ;

}
//Drawing the bricks
//--------------------------------------------
void draw ()
{
	glClear ( GL_COLOR_BUFFER_BIT );
	glColor3f(1.0,1.0,1.0);
	textures = loadTexture(images[6]);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textures);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glBegin ( GL_POLYGON ) ;
                glTexCoord2i(0.0,0.0);
                glVertex2i ( -300 , -200 ) ;
                glTexCoord2i(1.0,0.0);
                glVertex2i ( -320 , -200 ) ;
                glTexCoord2i(1.0,1.0);
                glVertex2i ( -320 , 300) ;
                glTexCoord2i(0.0,1.0);
                glVertex2i ( -300 , 300 ) ;
            glEnd () ;
            glBegin ( GL_POLYGON ) ;
                glTexCoord2i(0.0,0.0);
                glVertex2i ( 300 , -200 ) ;
                glTexCoord2i(1.0,0.0);
                glVertex2i ( 320 , -200 ) ;
                glTexCoord2i(1.0,1.0);
                glVertex2i ( 320 , 300) ;
                glTexCoord2i(0.0,1.0);
                glVertex2i ( 300 , 300 ) ;
            glEnd () ;
            glDisable(GL_TEXTURE_2D);
            glDeleteTextures(1,&textures);
            glFinish();
    glColor3f(1.0,1.0,1.0);
	for ( int j=0 ; j<i ; j++ )
	{
		if ( arr[j].value == 0 )
		{
		    glColor3f(0.0,0.0,0.0);
		    glPushMatrix();
		    glBegin ( GL_POLYGON ) ;
                glVertex2i ( arr[j].x1 , arr[j].y1 ) ;
                glVertex2i ( arr[j].x2 , arr[j].y1 ) ;
                glVertex2i ( arr[j].x2 , arr[j].y2) ;
                glVertex2i ( arr[j].x1 , arr[j].y2 ) ;
            glEnd ();
            glPopMatrix();
            glColor3f(1.0,1.0,1.0);
		}
        if ( arr[j].value == 1 )
        {
            textures = loadTexture(images[2]);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textures);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glBegin ( GL_POLYGON ) ;
                glTexCoord2i(0.0,0.0);
                glVertex2i ( arr[j].x1 , arr[j].y1 ) ;
                glTexCoord2i(1.0,0.0);
                glVertex2i ( arr[j].x2 , arr[j].y1 ) ;
                glTexCoord2i(1.0,1.0);
                glVertex2i ( arr[j].x2 , arr[j].y2) ;
                glTexCoord2i(0.0,1.0);
                glVertex2i ( arr[j].x1 , arr[j].y2 ) ;
            glEnd () ;
            glDisable(GL_TEXTURE_2D);
            glDeleteTextures(1,&textures);
            glFinish();
        }
        if ( arr[j].value == 2 )
        {
            textures = loadTexture(images[3]);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textures);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glBegin ( GL_POLYGON );
                glTexCoord2i(0.0,0.0);
                glVertex2i ( arr[j].x1 , arr[j].y1 ) ;
                glTexCoord2i(1.0,0.0);
                glVertex2i ( arr[j].x2 , arr[j].y1 ) ;
                glTexCoord2i(1.0,1.0);
                glVertex2i ( arr[j].x2 , arr[j].y2) ;
                glTexCoord2i(0.0,1.0);
                glVertex2i ( arr[j].x1 , arr[j].y2 ) ;
            glEnd () ;
            glDisable(GL_TEXTURE_2D);
            glDeleteTextures(1,&textures);
            glFinish();
        }
        if ( arr[j].value == 3 )
		{
            textures = loadTexture(images[4]);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textures);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glBegin ( GL_POLYGON );
                glTexCoord2i(0.0,0.0);
                glVertex2i ( arr[j].x1 , arr[j].y1 ) ;
                glTexCoord2i(1.0,0.0);
                glVertex2i ( arr[j].x2 , arr[j].y1 ) ;
                glTexCoord2i(1.0,1.0);
                glVertex2i ( arr[j].x2 , arr[j].y2) ;
                glTexCoord2i(0.0,1.0);
                glVertex2i ( arr[j].x1 , arr[j].y2 ) ;
            glEnd ();
            glDisable(GL_TEXTURE_2D);
            glDeleteTextures(1,&textures);
            glFinish();
		}
	}
	if(charactersFlag)
	{
	    question();
	    charactersFlag = false;
	}
}
//--------------------------------------------
void myDisplay()
{
    //case the game is finished
    //--------------------------------------------
    if(finishState)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0.3,0.2,0.5);
        drawText(tab2 ,strlen(tab2), -0.9, 0.7 );
        glColor3f(0.9,0,0.5);
        drawText("Collected Letters : " ,20, -0.7, 0.4 );
        drawText(saveTheAnswer ,strlen(saveTheAnswer), 0.05, 0.4 );
        glColor3f(0.3,0.2245,0.35661);
        drawText(readingAnswer ,strlen(readingAnswer), -0.3, 0.1 );
        glColor3f(1.0,1.0,1.0);
        if(gotRight)
        {
            if(hellYea)
            {
                PlaySound("D:\\Programming\\DX-Ball\\SFX\\clapping.wav",NULL,SND_ASYNC);
                hellYea = false;
            }
            glColor3f(0,1,0);
            drawText("Well Done !!" ,12, -0.2, -0.1 );
            glColor3f(1,1,1);
            go2NextLevel = true;
        }
        if(gotWrong)
        {

            if(hellNo)
            {
                PlaySound("D:\\Programming\\DX-Ball\\SFX\\boo.wav",NULL,SND_ASYNC);
                hellNo = false;
            }
            glColor3f(1,0,0);
            drawText("Nope !!" ,7, -0.2, -0.1 );
            glColor3f(1.0,1.0,1.0);
        }
    }//--------------------------------------------
    else//case of new game or game didn't finish
    {
        //--------------------------------------------
        freopen (readingFile,"r",stdin);
        if(scanningFlag == 1)
        {
            while ( scanf("%d",&x)!=EOF  )
            {
                if ( h+50 > 600 )
                {
                    h = 0 ;
                    v -=30 ;
                }
                if ( x !=0 )
                {
                    arr[i].x1=-300 + h;
                    arr[i].y1=300 + v ;
                    arr[i].x2=-300 + 50+h;
                    arr[i].y2= 300 -30+v ;
                    arr[i].value=x ;
                    i++;
                    h+=50;
                }
                else
                {
                    arr[i].x1=-300 + h;
                    arr[i].y1=300 + v ;
                    arr[i].x2=-300 + 50+h;
                    arr[i].y2= 300 -30+v ;
                    arr[i].value=x ;
                    i++;
                    h+=50;
                }
            }
        }
        scanningFlag = 0;
        if(getNewQuestion)
        {
            charactersFlag = true;
            getNewQuestion = false;
        }
        draw ();
        if ( hotpower )
        {
            bool a7eh [10];
            for ( int w=0 ; w<10 ; w++ )
            {
                while ( 1 )
                {
                    int lol = rand()%18;
                    if ( !a7eh[lol] )
                    {
                        arr[w].power=(rand()%2) +1;
                        a7eh[lol]=true;
                        break ;
                    }
                }
            }
            hotpower=false;
            memset ( a7eh , false , sizeof(a7eh) );
        }
        textures = loadTexture(images[0]);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textures);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBegin ( GL_POLYGON) ;
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f ( -70 + hBar , -215,0) ;
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f ( 70 +hBar , -215,0 ) ;
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f ( 70+ hBar , -200 ,0) ;
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f ( -70 + hBar , -200,0) ;
        glEnd ();
        glDisable(GL_TEXTURE_2D);
        glDeleteTextures(1,&textures);
            glFinish();
        textures = loadTexture(images[1]);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textures);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glPushMatrix();
        glBegin(GL_POLYGON);
        glColor3f(1.0,1.0,1.0);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(hBall-6,vBall-6,1);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(hBall+6,vBall-6,1);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(hBall+6,vBall+6,1);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(hBall-6,vBall+6,1);
        glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
        glDeleteTextures(1,&textures);
            glFinish();
        glColor3f(1,1,1);
        drawText("Score : " ,8, -1, -0.8 );
        glColor3f(1,0,1);
        drawText(score_string ,convert2String(1), -0.75, -0.8 );
        glColor3f(1,1,1);
        drawText("Life : " ,7, -1, -0.9 );
        glColor3f(1,0,1);
        drawText(life_string ,convert2String(2), -0.75, -0.9 );
        glColor3f(1,1,1);
        drawText("Collected Letters : " ,20, -0.2, -0.8 );
        glColor3f(1,0,1);
        drawText(saveTheAnswer ,strlen(saveTheAnswer), 0.45, -0.8 );
        glColor3f(1.0,1.0,1.0);
        drawText("Level : " ,8, -0.2, -0.9 );
        glColor3f(1,0,1);
        char fileNumChar[1];
        fileNumChar[0]= fileNum + '0';
        drawText(fileNumChar ,1, 0.15, -0.9 );
    }
    glutSwapBuffers();
}
//--------------------------------------------
//controlling the bar using the mouse
//--------------------------------------------
void myMouse(int x, int y)
{
    if(!finishState)
    {
        if(x <=300)
        {
            if(x >= 70 )
            {
                hBar = -300+x;
            }
        }
        else
        {
            if(x <=530)
            {
                hBar = x-300;
            }
        }
        if(startingState == 1)
                hBall = hBar ;
    }
    glutPostRedisplay();
}
//--------------------------------------------

void mouseClicks(int button, int state, int x, int y)
{
    if(!finishState)
    {
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            state1 = 1 ;
            state2 = 0 ;
        }
        if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {
            state1 = 0 ;
            state2 = 1 ;
        }
    }
}
// all the work and conditions and everything works here
//--------------------------------------------
void myTimer(int val)
{
    int j;
    for(j=0;j<i;j++)
    {
        //checking for hitting a brick
        //--------------------------------------------
        if(hBall+xIncr+(6*xIncr)/abs(xIncr) >arr[j].x1 &&hBall+xIncr+(6*xIncr)/abs(xIncr) <arr[j].x2 && vBall+(6*yIncr)/abs(yIncr) +yIncr >arr[j].y2 && vBall+(6*yIncr)/abs(yIncr) +yIncr <arr[j].y1)
        {
            if(yIncr>0)
            {
                if(xIncr>0)
                {
                    /*
                        ball will be like
                        3------*--
                        2-----*---
                        1----*----
                    */
                    //if i hit the brick from the left side
                    if(hBall+xIncr+6 >=arr[j].x1 &&hBall+xIncr+6 <=arr[j].x2 && vBall>=arr[j].y2&& vBall<=arr[j].y1 )
                    {
                        if(arr[j].value >0)
                        {
                            if(power1)
                            {
                                arr[j].value = 0;
                                score += arr[j].value*5;
                                if(arr[j].character >=97 && arr[j].character<=123 && arr[j].value == 0 )
                                {
                                    saveTheAnswer[saveAnswer] = arr[j].character;
                                    arr[j].character = '\0';
                                    saveAnswer ++;
                                }
                            }
                            else
                            {
                                xIncr *= -1;
                                arr[j].value--;
                                score+=5;
                                if(arr[j].character >=97 && arr[j].character<=123 && arr[j].value == 0 )
                                {
                                    saveTheAnswer[saveAnswer] = arr[j].character;
                                    arr[j].character = '\0';
                                    saveAnswer ++;
                                }
                                if(arr[j].value == 0)
                                {
                                    if ( arr[j].power==1 )
                                    {
                                        power1=true ;
                                        arr[j].power = 0;
                                        PlaySound("D:\\Programming\\DX-Ball\\SFX\\sinewave.wav",NULL,SND_ASYNC);
                                    }
                                    else if(arr[j].power == 2)
                                    {
                                        power2 = true;
                                        arr[j].power = 0;
                                        endTimer+=300;
                                        startCounter = true;
                                        PlaySound("D:\\Programming\\DX-Ball\\SFX\\whoosh.wav",NULL,SND_ASYNC);
                                    }
                                    else
                                        PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Bang.wav",NULL,SND_ASYNC);
                                }
                                else
                                    PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Boing.wav",NULL,SND_ASYNC);
                            }
                        }
                    }
                    // if i hit the brick from the down side
                    if(hBall >=arr[j].x1 &&hBall <=arr[j].x2 && vBall+yIncr+6>=arr[j].y2&& vBall+yIncr+6<=arr[j].y1 )
                    {
                        if(arr[j].value >0)
                        {
                            if(power1)
                            {
                                arr[j].value = 0;
                                score += arr[j].value*5;
                                if(arr[j].character >=97 && arr[j].character<=123 && arr[j].value == 0 )
                                {
                                    saveTheAnswer[saveAnswer] = arr[j].character;
                                    arr[j].character = '\0';
                                    saveAnswer ++;
                                }
                            }
                            else
                            {
                                yIncr *= -1;
                                arr[j].value--;
                                score+=5;
                                if(arr[j].character >=97 && arr[j].character<=123 && arr[j].value == 0 )
                                {
                                    saveTheAnswer[saveAnswer] = arr[j].character;
                                    arr[j].character = '\0';
                                    saveAnswer ++;
                                }
                                if(arr[j].value == 0)
                                {
                                    if ( arr[j].power==1 )
                                    {
                                        power1=true ;
                                        arr[j].power = 0;
                                        PlaySound("D:\\Programming\\DX-Ball\\SFX\\sinewave.wav",NULL,SND_ASYNC);
                                    }
                                    else if(arr[j].power == 2)
                                    {
                                        power2 = true;
                                        arr[j].power = 0;
                                        endTimer+=300;
                                        startCounter = true;
                                        PlaySound("D:\\Programming\\DX-Ball\\SFX\\whoosh.wav",NULL,SND_ASYNC);
                                    }
                                    else
                                        PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Bang.wav",NULL,SND_ASYNC);
                                }
                                else
                                    PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Boing.wav",NULL,SND_ASYNC);
                            }
                        }
                    }
                }
                else
                {
                    /*ball will be like
                    3----*----
                    2-----*---
                    1------*--
                    */
                    //hitting the brick from the right side
                    if(hBall+xIncr-6 >=arr[j].x1 &&hBall+xIncr-6 <=arr[j].x2 && vBall>=arr[j].y2&& vBall<=arr[j].y1 )
                    {
                        if(arr[j].value >0)
                        {
                            if(power1)
                            {
                                arr[j].value = 0;
                                score += arr[j].value*5;
                                if(arr[j].character >=97 && arr[j].character<=123 && arr[j].value == 0 )
                                {
                                    saveTheAnswer[saveAnswer] = arr[j].character;
                                    arr[j].character = '\0';
                                    saveAnswer ++;
                                }
                            }
                            else if(arr[j].power == 0)
                            {
                                xIncr *= -1;
                                arr[j].value--;
                                score+=5;
                                if(arr[j].character >=97 && arr[j].character<=123 && arr[j].value == 0 )
                                {
                                    saveTheAnswer[saveAnswer] = arr[j].character;
                                    arr[j].character = '\0';
                                    saveAnswer ++;
                                }
                                if(arr[j].value == 0)
                                {
                                    if ( arr[j].power==1 )
                                    {
                                        power1=true ;
                                        arr[j].power = 0;
                                        PlaySound("D:\\Programming\\DX-Ball\\SFX\\sinewave.wav",NULL,SND_ASYNC);
                                    }
                                    else if(arr[j].power == 2)
                                    {
                                        power2 = true;
                                        arr[j].power = 0;
                                        endTimer+=300;
                                        startCounter = true;
                                        PlaySound("D:\\Programming\\DX-Ball\\SFX\\whoosh.wav",NULL,SND_ASYNC);
                                    }
                                    else
                                        PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Bang.wav",NULL,SND_ASYNC);
                                }
                                else
                                    PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Boing.wav",NULL,SND_ASYNC);
                            }
                        }
                    }
                    //hitting the brick from the down side
                    if(hBall >=arr[j].x1 &&hBall <=arr[j].x2 && vBall+yIncr+6>=arr[j].y2&& vBall+yIncr+6<=arr[j].y1 )
                    {
                        if(arr[j].value >0)
                        {
                            if(power1)
                            {
                                arr[j].value = 0;
                                score += arr[j].value*5;
                                if(arr[j].character >=97 && arr[j].character<=123 && arr[j].value == 0 )
                                {
                                    saveTheAnswer[saveAnswer] = arr[j].character;
                                    arr[j].character = '\0';
                                    saveAnswer ++;
                                }
                            }
                            else if(arr[j].power == 0)
                            {
                                yIncr *= -1;
                                arr[j].value--;
                                score+=5;
                                if(arr[j].character >=97 && arr[j].character<=123 && arr[j].value == 0 )
                                {
                                    saveTheAnswer[saveAnswer] = arr[j].character;
                                    arr[j].character = '\0';
                                    saveAnswer ++;
                                }
                                if(arr[j].value == 0)
                                {
                                    if ( arr[j].power==1 )
                                    {
                                        power1=true ;
                                        arr[j].power = 0;
                                        PlaySound("D:\\Programming\\DX-Ball\\SFX\\sinewave.wav",NULL,SND_ASYNC);
                                    }
                                    else if(arr[j].power == 2)
                                    {
                                        power2 = true;
                                        arr[j].power = 0;
                                        endTimer+=300;
                                        startCounter = true;
                                        PlaySound("D:\\Programming\\DX-Ball\\SFX\\whoosh.wav",NULL,SND_ASYNC);
                                    }
                                    else
                                        PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Bang.wav",NULL,SND_ASYNC);
                                }
                                else
                                    PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Boing.wav",NULL,SND_ASYNC);
                            }
                        }
                    }
                }
            }
            else
            {
                /*
                        ball will be like
                        1----*----
                        2-----*---
                        3------*--
                    */
                if(xIncr>0)
                {
                    //hitting the brick from the left side
                    if(hBall+xIncr+6 >=arr[j].x1 &&hBall+xIncr+6 <=arr[j].x2 && vBall>=arr[j].y2&& vBall<=arr[j].y1 )
                    {
                        if(arr[j].value >0)
                        {
                            if(power1)
                            {
                                arr[j].value = 0;
                                score += arr[j].value*5;
                                if(arr[j].character >=97 && arr[j].character<=123 && arr[j].value == 0 )
                                {
                                    saveTheAnswer[saveAnswer] = arr[j].character;
                                    arr[j].character = '\0';
                                    saveAnswer ++;
                                }
                            }
                            else if(arr[j].power == 0)
                            {
                                xIncr *= -1;
                                arr[j].value--;
                                score+=5;
                                if(arr[j].character >=97 && arr[j].character<=123 && arr[j].value == 0 )
                                {
                                    saveTheAnswer[saveAnswer] = arr[j].character;
                                    arr[j].character = '\0';
                                    saveAnswer ++;
                                }
                                if(arr[j].value == 0)
                                {
                                    if ( arr[j].power==1 )
                                    {
                                        power1=true ;
                                        arr[j].power = 0;
                                        PlaySound("D:\\Programming\\DX-Ball\\SFX\\sinewave.wav",NULL,SND_ASYNC);
                                    }
                                    else if(arr[j].power == 2)
                                    {
                                        power2 = true;
                                        arr[j].power = 0;
                                        endTimer+=300;
                                        startCounter = true;
                                        PlaySound("D:\\Programming\\DX-Ball\\SFX\\whoosh.wav",NULL,SND_ASYNC);
                                    }
                                    else
                                        PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Bang.wav",NULL,SND_ASYNC);
                                }
                                else
                                    PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Boing.wav",NULL,SND_ASYNC);
                            }
                        }
                    }
                    //hitting the brick from the upper side
                    if(hBall >=arr[j].x1 &&hBall <=arr[j].x2 && vBall+yIncr-6>=arr[j].y2&& vBall+yIncr-6<=arr[j].y1 )
                    {
                        if(arr[j].value >0)
                        {
                            if(power1)
                            {
                                arr[j].value = 0;
                                score += arr[j].value*5;
                                if(arr[j].character >=97 && arr[j].character<=123 && arr[j].value == 0 )
                                {
                                    saveTheAnswer[saveAnswer] = arr[j].character;
                                    arr[j].character = '\0';
                                    saveAnswer ++;
                                }
                            }
                            else if(arr[j].power == 0)
                            {
                                yIncr *= -1;
                                arr[j].value--;
                                score+=5;
                                if(arr[j].character >=97 && arr[j].character<=123 && arr[j].value == 0 )
                                {
                                    saveTheAnswer[saveAnswer] = arr[j].character;
                                    arr[j].character = '\0';
                                    saveAnswer ++;
                                }
                                if(arr[j].value == 0)
                                {
                                    if ( arr[j].power==1 )
                                    {
                                        power1=true ;
                                        arr[j].power = 0;
                                        PlaySound("D:\\Programming\\DX-Ball\\SFX\\sinewave.wav",NULL,SND_ASYNC);
                                    }
                                    else if(arr[j].power == 2)
                                    {
                                        power2 = true;
                                        arr[j].power = 0;
                                        endTimer+=300;
                                        startCounter = true;
                                        PlaySound("D:\\Programming\\DX-Ball\\SFX\\whoosh.wav",NULL,SND_ASYNC);
                                    }
                                    else
                                        PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Bang.wav",NULL,SND_ASYNC);
                                }
                                else
                                    PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Boing.wav",NULL,SND_ASYNC);
                            }
                        }
                    }
                }
                else
                {
                    /*ball will be like
                        1------*--
                        2-----*---
                        3----*----*/
                    // hitting the brick form the right side
                    if(hBall+xIncr-6 >=arr[j].x1 &&hBall+xIncr-6 <=arr[j].x2 && vBall>=arr[j].y2&& vBall<=arr[j].y1 )
                    {
                        if(arr[j].value >0)
                        {
                            if(power1)
                            {
                                arr[j].value = 0;
                                score += arr[j].value*5;
                                if(arr[j].character >=97 && arr[j].character<=123 && arr[j].value == 0 )
                                {
                                    saveTheAnswer[saveAnswer] = arr[j].character;
                                    arr[j].character = '\0';
                                    saveAnswer ++;
                                }
                            }
                            else if(arr[j].power == 0)
                            {
                                xIncr *= -1;
                                arr[j].value--;
                                score+=5;
                                if(arr[j].character >=97 && arr[j].character<=123 && arr[j].value == 0 )
                                {
                                    saveTheAnswer[saveAnswer] = arr[j].character;
                                    arr[j].character = '\0';
                                    saveAnswer ++;
                                }
                                else if(arr[j].value == 0)
                                {
                                    if ( arr[j].power==1 )
                                    {
                                        power1=true ;
                                        arr[j].power = 0;
                                        PlaySound("D:\\Programming\\DX-Ball\\SFX\\sinewave.wav",NULL,SND_ASYNC);
                                    }
                                    if(arr[j].power == 2)
                                    {
                                        power2 = true;
                                        arr[j].power = 0;
                                        endTimer+=300;
                                        startCounter = true;
                                        PlaySound("D:\\Programming\\DX-Ball\\SFX\\whoosh.wav",NULL,SND_ASYNC);
                                    }
                                    else
                                        PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Bang.wav",NULL,SND_ASYNC);
                                }
                                else
                                    PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Boing.wav",NULL,SND_ASYNC);
                            }
                        }
                    }
                    //hitting the brick from the upper side
                    if(hBall >=arr[j].x1 &&hBall <=arr[j].x2 && vBall+yIncr-6>=arr[j].y2&& vBall+yIncr-6<=arr[j].y1 )
                    {
                        if(arr[j].value >0)
                        {
                            if(power1)
                            {
                                arr[j].value = 0;
                                score += arr[j].value*5;
                                if(arr[j].character >=97 && arr[j].character<=123 && arr[j].value == 0 )
                                {
                                    saveTheAnswer[saveAnswer] = arr[j].character;
                                    arr[j].character = '\0';
                                    saveAnswer ++;
                                }
                            }
                            else if(arr[j].power == 0)
                            {
                                yIncr *= -1;
                                arr[j].value--;
                                score+=5;
                                if(arr[j].character >=97 && arr[j].character<=123 && arr[j].value == 0 )
                                {
                                    saveTheAnswer[saveAnswer] = arr[j].character;
                                    arr[j].character = '\0';
                                    saveAnswer ++;
                                }
                                if(arr[j].value == 0)
                                {
                                    if ( arr[j].power==1 )
                                    {
                                        power1=true ;
                                        arr[j].power = 0;
                                        PlaySound("D:\\Programming\\DX-Ball\\SFX\\sinewave.wav",NULL,SND_ASYNC);
                                    }
                                    else if(arr[j].power == 2)
                                    {
                                        power2 = true;
                                        arr[j].power = 0;
                                        endTimer+=300;
                                        startCounter = true;
                                        PlaySound("D:\\Programming\\DX-Ball\\SFX\\whoosh.wav",NULL,SND_ASYNC);
                                    }
                                    else
                                        PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Bang.wav",NULL,SND_ASYNC);
                                }
                                else
                                    PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Boing.wav",NULL,SND_ASYNC);
                            }
                        }
                    }
                }
            }

            draw();
            glDeleteTextures(1,&textures);
            glFinish();
            winningFlag = true;
            for(j=0;j<i;j++)
            {
                if(arr[j].value>0)
                    winningFlag = false;
            }
            if(winningFlag)
            {
                xIncr = 0;
                yIncr = 0;
                finishState = true;
                winningFlag = false;
                glutPostRedisplay();
            }
        }
    }
    //--------------------------------------------
    if(yIncr >0)
    {
        if(xIncr>0)
        {
            if(hBall + xIncr +6 > 300)
            {
                xIncr *= -1;
                PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Swordswi.wav",NULL,SND_ASYNC);
            }
            if(vBall+yIncr+6 > 300)
            {
                yIncr *= -1;
                PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Swordswi.wav",NULL,SND_ASYNC);
            }
        }
        else
        {
            if(hBall + xIncr -6 <-300)
            {
                xIncr *= -1;
                PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Swordswi.wav",NULL,SND_ASYNC);
            }
            if(vBall +yIncr +6 >300)
            {
                yIncr *= -1;
                PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Swordswi.wav",NULL,SND_ASYNC);
            }
        }

    }
    else
    {
        if(xIncr > 0)
        {
            if(hBall + xIncr +6 > 300)
            {
                xIncr *= -1;
                PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Swordswi.wav",NULL,SND_ASYNC);
            }
            if(hBall+xIncr+6 >= hBar-70 &&hBall+xIncr+6 <= hBar-20 && vBall +yIncr <-200 && vBall +yIncr >-210)
            {
                xIncr *= -1;
                yIncr *= -1;
                PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Swordswi.wav",NULL,SND_ASYNC);
            }
            if(hBall+xIncr+6 >= hBar-20 &&hBall+xIncr+6 <= hBar+70 && vBall +yIncr <-200 && vBall +yIncr >-210)
            {
                yIncr *= -1;
                PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Swordswi.wav",NULL,SND_ASYNC);
            }
        }
        else
        {
            if(hBall + xIncr -6 <-300)
            {
                xIncr *= -1;
                PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Swordswi.wav",NULL,SND_ASYNC);
            }
            if(hBall+xIncr+6 <= hBar+70 &&hBall+xIncr+6 >= hBar+20 && vBall +yIncr <-200 && vBall +yIncr >-210)
            {
                xIncr *= -1;
                yIncr *= -1;
                PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Swordswi.wav",NULL,SND_ASYNC);
            }
            if(hBall+xIncr+6 <= hBar+20 &&hBall+xIncr+6 >= hBar-70 && vBall +yIncr <-200 && vBall +yIncr >-210)
            {
                yIncr *= -1;
                PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Swordswi.wav",NULL,SND_ASYNC);
            }
        }
    }
    if(hBall+6 >300 || hBall-6 < -300)
    {
        xIncr *= -1;
        PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Swordswi.wav",NULL,SND_ASYNC);
    }
    if(vBall+6 > 300 )
    {
        yIncr *= -1;
        PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Swordswi.wav",NULL,SND_ASYNC);
    }
    if(vBall -6 <-300)
    {
        state1 = 0;
        state2 = 1;
        life--;
        PlaySound("D:\\Programming\\DX-Ball\\Sounds\\Padexplo.wav",NULL,SND_ASYNC);
        if(life<0)
            state3 = 1;
    }
    if(go2NextLevel)
    {
        Sleep(5000);

        fileNum++;
        if(fileNum >3)
        {
            fileNum = 1;
        }
        changeFile();
        startingState = 1;
        scanningFlag = 1;
        vBall = -194;
        hBall = hBar;
        power1 = false;
        power2 = false;
        powerCounter =0;
        endTimer = 0;
        startCounter = false;
        xIncr = 7;
        yIncr = 7;
        flag2 = !flag2;
        flag = 1;
        h=0;
        v=0;
        i=0;
        readingAnswerCounter = 0;
        saveAnswer =0;
        memset(saveTheAnswer,0,strlen(saveTheAnswer));
        memset(readingAnswer,0,strlen(readingAnswer));
        go2NextLevel = false;
        finishState = false;
        winningFlag = false;
        gotRight = false;
        gotWrong = false;
        getNewQuestion = true;
        hotpower = true;
    }
    if(state1 == 1)
    {
        startingState = 0;
        if(flag == 1)
        {
            hBall += xIncr ;
            vBall += yIncr ;
        }
    }
    if(state2 == 1)
    {
        startingState = 1;
        vBall = -194;
        hBall = hBar;
        xIncr = 7;
        yIncr = 7;
        flag2 = !flag2;
        flag = 1;
    }
    if(state3 == 1)
    {
        fileNum = 1;
        score = 0;
        life = 3;
        h=0;
        v=0;
        scanningFlag = 1;
        startingState = 1;
        vBall = -198;
        hBall = hBar;
        xIncr = 7;
        yIncr = 7;
        flag2 = !flag2;
        flag = 1;
        state3 = 0;
    }
    if(startCounter)
    {
        if(power2)
        {
            if(xIncr > 0)
                xIncr =12;
            else
                xIncr -12;
            if(yIncr > 0)
                yIncr =12;
            else
                yIncr =-12;
        }
        powerCounter ++;
        if(powerCounter >= endTimer)
        {
            endTimer = 0;
            powerCounter = 0;
            startCounter = false;
            if(xIncr > 0)
                xIncr -=5;
            else
                xIncr +=5;
            if(yIncr > 0)
                yIncr -=5;
            else
                yIncr +=5;
        }
    }
    glDeleteTextures(1,&textures);
    glFinish();
    glutPostRedisplay();
    glutTimerFunc(100,myTimer,0);
}
void keyboard(unsigned char ch , int x , int y)
{
    if(finishState)
    {
        for (int justCounter =0;justCounter < sizeof(saveTheAnswer);justCounter++)
        {
            if(ch == saveTheAnswer[justCounter])
            {
                if(readingAnswerCounter < 20)
                {
                    readingAnswer[readingAnswerCounter] = ch;
                    readingAnswerCounter++;
                    break;
                }
            }
        }
        if(ch == (char)13)
        {
            if(comp(readingAnswer,strlen(readingAnswer),theAnswer,strlen(theAnswer)))
            {
                hellYea = true;
                hellNo = false;
                gotRight = true;
                gotWrong = false;
            }
            else
            {

                hellNo = true;
                hellYea = false;
                gotRight = false;
                gotWrong = true;
            }
        }
        if(ch == (char)8)
        {
            if(readingAnswerCounter>0)
            {
                readingAnswerCounter--;
                readingAnswer[readingAnswerCounter] = '\0';
            }
        }
    }
    glutPostRedisplay();
}
void specialKeyBoard(int key ,int x ,int y)
{
    if(key == GLUT_KEY_F1)
    {
        saveAns();
        winningFlag = true;
        finishState = true;
        glutPostRedisplay();
    }
    if(key == GLUT_KEY_F4)
        exit(0);
    return;
}
int main ( int argc , char ** argv )
{
    glutInit(&argc , argv ) ;
    glEnable(GL_TEXTURE_2D);
    getAllPics();
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB  | GLUT_DEPTH);
    glutInitWindowSize (800 , 600) ;
    glutInitWindowPosition (50 , 50) ;
    glutCreateWindow ("DX-Ball");
    myStyleInit();
    glutMouseFunc(mouseClicks);
    glutPassiveMotionFunc(myMouse);
    glutTimerFunc(100,myTimer,0);
    glutDisplayFunc ( myDisplay ) ;
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyBoard);
    glutMainLoop () ;
    return 0 ;
}
