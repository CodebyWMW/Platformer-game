#include "iGraphics.h"

char homemenu[]="assets/images/Menufinal.bmp";
char bg[]="assets/images/background.bmp";
char inst[]="assets/images/Instructions.bmp";
char tileImage[] = "assets/images/Tilemodel2.bmp"; 
enum
{
	IDLE,
	WALK,
	JUMP
};

int sprite_x = 43;
 int sprite_y = 200;
 int jump = 0; // 0 = not jumping, 1 = jumping
int jump_peak = 100; // how high to jump
int jump_start_y = 0;
int pic_x, pic_y;
int state = IDLE;
int direction = 1; // 1 for right, -1 for left

Image idleMonster[4], walkMonster[6], jumpMonster[8];
Sprite monster;

void loadResources()
{
	iLoadFramesFromSheet(idleMonster, "assets/images/sprites/1 Pink_Monster/Pink_Monster_Idle_4.png", 1, 4);
	iLoadFramesFromSheet(walkMonster, "assets/images/sprites/1 Pink_Monster/Pink_Monster_Walk_6.png", 1, 6);
	iLoadFramesFromSheet(jumpMonster, "assets/images/sprites/1 Pink_Monster/Pink_Monster_Jump_8.png", 1, 8);

	iInitSprite(&monster, -1);
	iChangeSpriteFrames(&monster, idleMonster, 4);
	iSetSpritePosition(&monster, 20, 0);
	iScaleSprite(&monster, 3.0);
}

void updateMonster()
{
	switch (state)
	{
	case IDLE:
		break;
	case WALK:
		break;
	case JUMP:
		if (monster.y == 0)
		{
			state = IDLE;
			iChangeSpriteFrames(&monster, idleMonster, 4);
		}
		break;
	}
	iAnimateSprite(&monster);
	monster.y = (monster.y - 1 > 0) ? (monster.y - 1) : 0;
}
/*
function iDraw() is called again and again by the system.
*/
int gamestate=0;
void iDraw()
{
    iClear();

    if (gamestate == 0)
    {
        iShowImage(0, 0, homemenu); // Show menu
    }
    else if (gamestate == 1)
    {
        iShowImage(0, 0, bg); // Show background for game
        iShowImage(168,315, tileImage); 
         iShowImage(420,500, tileImage);// Show tile image (example size 128x128)
        // Draw grid of tiles
        iSetSpritePosition(&monster, sprite_x, sprite_y);
       	iShowSprite(&monster);
    }
    else if (gamestate == 2)
    {
        iShowImage(0, 0, inst); // Show instructions
    }
}

/*
function iMouseMove() is called when the user moves the mouse.
(mx , my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    // place your codes here
}

/*
function iMouseDrag() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseDrag(int mx, int my)
{
    // place your codes here
}

/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Start button area: x: 364–767, y: 452–542
        if (mx >= 364 && mx <= 767 && my >= 452 && my <= 542)
        {
            // Start button clicked!
            gamestate = 1; // Or any action you want
        }
        // Instructions button area: x: 385–780, y: 540–600
        if (mx >= 385 && mx <= 780 && my >= 140 && my <= 200)
        {
            // Instructions button clicked!
            gamestate = 2; // Or any action you want for instructions
        }
          else if ( gamestate == 2)
        {
            gamestate = 0; // Any click returns to main menu
        }
    }
    }
   

/*
function iMouseWheel() is called when the user scrolls the mouse wheel.
dir = 1 for up, -1 for down.
*/
void iMouseWheel(int dir, int mx, int my)
{
    // place your code here
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    switch (key)
    {
    case 'q':
        // do something with 'q'
        break;
    // place your codes for other keys here
    default:
        break;
    }
    
	if (key == 'x')
	{
		// do something with 'x'
		exit(0);
	}
}

/*
function iSpecialKeyboard() is called whenver user hits special keys likefunction
keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11,
GLUT_KEY_F12, GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN,
GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN, GLUT_KEY_HOME, GLUT_KEY_END,
GLUT_KEY_INSERT */
void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
    if(gamestate==1){
	if (key == GLUT_KEY_LEFT)
	{
		if (direction == 1)
		{
			iMirrorSprite(&monster, HORIZONTAL);
			direction = -1;
            sprite_x -= 10; // Move left by 10 pixels
        
		}}
		else
		{
			monster.x--;
			if (state != WALK)
			{
				state = WALK;
				iChangeSpriteFrames(&monster, walkMonster, 6);
			}
		}
	}
	if (key == GLUT_KEY_RIGHT)
	{
		if (direction == -1)
		{
			iMirrorSprite(&monster, HORIZONTAL);
			direction = 1;
		}
		else
		{
			monster.x++;
			if (state != WALK)
			{
				state = WALK;
				iChangeSpriteFrames(&monster, walkMonster, 6);
			}
		}
	}
	if (key == GLUT_KEY_UP)
	{
		monster.y++;
		if (state != JUMP)
		{
			state = JUMP;
			iChangeSpriteFrames(&monster, jumpMonster, 8);
		}
	}
	if (key == GLUT_KEY_DOWN)
	{
		monster.y--;
	}
	// place your codes for other keys here
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    
    loadResources();
    iSetTimer(100, updateMonster);
    // place your own initialization codes here.
    iInitialize(1200, 800, "demooo");
  
    return 0;
}