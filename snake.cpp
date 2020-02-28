/*
<<<<<<< HEAD
CS 349 A1 Skeleton Code - Snake

- - - - - - - - - - - - - - - - - - - - - -

Commands to compile and run:

    g++ -o snake snake.cpp -L/usr/X11R6/lib -lX11 -lstdc++
    ./snake

Note: the -L option and -lstdc++ may not be needed on some machines.
*/

#include <iostream>
=======
   CS 349 A1 Skeleton Code - Snake

   - - - - - - - - - - - - - - - - - - - - - -

   Commands to compile and run:

   g++ -o snake snake.cpp -L/usr/X11R6/lib -lX11 -lstdc++
   ./snake

Note: the -L option and -lstdc++ may not be needed on some machines.
 */

#include <iostream>
#include <sstream>
>>>>>>> d6e3ff51e286dc507d30a4fd2cb6a9910167fdc2
#include <list>
#include <cstdlib>
#include <sys/time.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
<<<<<<< HEAD
=======
//#include <string>
//#include <vector>
#include "snake.h"
>>>>>>> d6e3ff51e286dc507d30a4fd2cb6a9910167fdc2

/*
 * Header files for X functions
 */
<<<<<<< HEAD
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;
 
=======
//#include <X11/Xlib.h>
//#include <X11/Xutil.h>

using namespace std;

>>>>>>> d6e3ff51e286dc507d30a4fd2cb6a9910167fdc2
/*
 * Global game state variables
 */
const int Border = 1;
const int BufferSize = 10;
<<<<<<< HEAD
const int FPS = 30;
const int width = 800;
const int height = 600;

/*
 * Information to draw on the window.
 */
struct XInfo {
	Display	 *display;
	int		 screen;
	Window	 window;
	GC		 gc[3];
	int		width;		// size of window
	int		height;
};
=======
int FPS = 30;
const int width = 800;
const int height = 600;
int snakespeed = 5;
bool pauseFlag = false;
const int blockSize = 50;
bool startGame = true;
bool GameOver = false;
int countInvincibility = 0;
bool flagInv = false;
bool restartFlag = false;

list<Displayable *> dList;
Snake snake(100, 450);
Fruit fruit;
Score score;
Obstacle obstacle;
Invincibility invincibility;
>>>>>>> d6e3ff51e286dc507d30a4fd2cb6a9910167fdc2


/*
 * Function to put out a message on error exits.
 */
void error( string str ) {
  cerr << str << endl;
  exit(0);
}


/*
 * An abstract class representing displayable things. 
 */
<<<<<<< HEAD
class Displayable {
	public:
		virtual void paint(XInfo &xinfo) = 0;
};       

class Snake : public Displayable {
	public:
		virtual void paint(XInfo &xinfo) {
			XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], x, y, 25, blockSize);
		}
		
		void move(XInfo &xinfo) {
			x = x + direction;
			if (x < 0 || x > width) {
				direction = -direction;
			}

            // ** ADD YOUR LOGIC **
            // Here, you will be performing collision detection between the snake, 
            // the fruit, and the obstacles depending on what the snake lands on.
		}
		
		int getX() {
			return x;
		}
		
		int getY() {
			return y;
		}

        /*
         * ** ADD YOUR LOGIC **
         * Use these placeholder methods as guidance for implementing the snake behaviour. 
         * You do not have to use these methods, feel free to implement your own.
         */ 
        void didEatFruit() {
        }

        void didHitObstacle() {
        }

        void turnLeft() {
        }

        void turnRight() {
        }
		
		Snake(int x, int y): x(x), y(y) {
			direction = 5;
            blockSize = 10;
		}
	
	private:
		int x;
		int y;
		int blockSize;
		int direction;
};

class Fruit : public Displayable {
	public:
		virtual void paint(XInfo &xinfo) {
			XFillRectangle(xinfo.display, xinfo.window, xinfo.gc[0], x, y, 10, 10);
        }

        Fruit() {
            // ** ADD YOUR LOGIC **
            // generate the x and y value for the fruit 
            x = 50;
            y = 50;
        }

        // ** ADD YOUR LOGIC **
        /*
         * The fruit needs to be re-generated at new location every time a snake eats it. See the assignment webpage for more details.
         */

    private:
        int x;
        int y;
};


list<Displayable *> dList;           // list of Displayables
Snake snake(100, 450);
Fruit fruit;
=======

void Invincibility::paint(XInfo &xinfo) {
  XPoint points[] = {
    {x, y},
    {x, y + blockSize},
    {x + blockSize, y + blockSize},
    {x, y}
  };
  int npoints = sizeof(points) / sizeof(XPoint);
  XDrawLines(xinfo.display, xinfo.pixmap, xinfo.gc[0], points, npoints, CoordModeOrigin);
}

void Invincibility::restart() {
  invincibility = Invincibility();
}

Invincibility::Invincibility() {
  while(true) {
    x = rand()%(width/blockSize) * blockSize;
    y = rand()%(height/blockSize) * blockSize;

    if (!checkSnakeOverlap(snake) && !checkFruitOverlap(fruit) && !checkObstacleOverlap(obstacle)) {
      break;
    }
  }
}

bool Invincibility::checkSnakeOverlap(Snake &snake) {
  vector <vector <int> > snakePosition = snake.getPosition();
  int snakeLength = snakePosition.size();

  for (int i = 0; i < snakeLength; ++i) {
    if (x == snakePosition[i][0] && y == snakePosition[i][1]) {
      return true;
    }
  }
  return false;
}

bool Invincibility::checkFruitOverlap(Fruit &fruit) {
  if (x == fruit.getX() && y == fruit.getY()) {
    return true;
  }
  return false;
}

bool Invincibility::checkObstacleOverlap(Obstacle &obstacle) {
  vector <vector <int> > obstaclePosition = obstacle.getObstacles();
  int obstacleLength = obstaclePosition.size();

  for (int i = 0; i < obstacleLength; ++i) {
    if (x == obstaclePosition[i][0] && y == obstaclePosition[i][1]) {
      return true;
    }
  }
  return false;
}

int Invincibility::getX() {
  return x;
}

int Invincibility::getY() {
  return y;
}



void Score::paint(XInfo &xinfo) {
  string sc = "Score: " + scoreNumberString;
  XDrawImageString(xinfo.display, xinfo.pixmap, xinfo.gc[0], x, y, sc.c_str(), sc.length());
}

void Score::restart() {
  scoreNumber = 0;
  scoreNumberString = "0";
}

Score::Score() {
  scoreNumber = 0;
  x = 50;
  y = 50;
  scoreNumberString = "0";
}

void Score::updateScore() {
  scoreNumber++;
}

void Score::convertString() {
  stringstream ss;
  ss << scoreNumber;
  scoreNumberString = ss.str();
}

string Score::getScoreString() {
  return scoreNumberString;
}



void Obstacle::paint(XInfo &xinfo) {
  int length = position.size();
  for (int i = 0; i < length; ++i) {
    XDrawRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], position[i][0], position[i][1], blockSize, blockSize);
    XDrawLine(xinfo.display, xinfo.pixmap, xinfo.gc[0], position[i][0], position[i][1], position[i][0] + blockSize, position[i][1] + blockSize);
    XDrawLine(xinfo.display, xinfo.pixmap, xinfo.gc[0], position[i][0] + blockSize, position[i][1], position[i][0], position[i][1] + blockSize);
  }
}

void Obstacle::restart() {
  for (int i = 0; i < num_obstacles; ++i) {
    position.pop_back();
  }

  num_obstacles = rand()%10 + min_num_obstacles;
  for (int i = 0; i < num_obstacles; ++i) {
    int x = rand()%(width/blockSize) * blockSize;
    int y = rand()%(height/blockSize) * blockSize;

    while (checkSnakeOverlap(x, y, snake) || checkFruitOverlap(x, y, fruit)) {
      x = rand()%(width/blockSize) * blockSize;
      y = rand()%(height/blockSize) * blockSize;
    }

    vector <int> obs;
    obs.push_back(x);
    obs.push_back(y);
    position.push_back(obs);
  }
}

Obstacle::Obstacle() {
  min_num_obstacles;
  num_obstacles = rand()%10 + min_num_obstacles;

  for (int i = 0; i < num_obstacles; ++i) {
    int x = rand()%(width/blockSize) * blockSize;
    int y = rand()%(height/blockSize) * blockSize;

    while (checkSnakeOverlap(x, y, snake) || checkFruitOverlap(x, y, fruit)) {
      x = rand()%(width/blockSize) * blockSize;
      y = rand()%(height/blockSize) * blockSize;
    }

    vector <int> obs;
    obs.push_back(x);
    obs.push_back(y);
    position.push_back(obs);
  }
}

bool Obstacle::checkSnakeOverlap(int x, int y, Snake &snake) {
  vector <vector <int> > snakePosition = snake.getPosition();
  int snakeLength = snakePosition.size();
  for (int i = 0; i < snakeLength; ++i) {
    if (x == snakePosition[i][0] && y == snakePosition[i][1]) {
      return true;
    }
  }
  return false;
}

bool Obstacle::checkFruitOverlap(int x, int y, Fruit &fruit) {
  if (x == fruit.getX() && y == fruit.getY()) {
    return true;
  }
  return false;
}

vector <vector <int> > Obstacle::getObstacles() {
  return position;
}



void Fruit::paint(XInfo &xinfo) {
  XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x, y, blockSize, blockSize);
}

void Fruit::restart() {
  vector <vector <int> > snakePosition = snake.getPosition();
  int snakeLength = snakePosition.size();
  bool flag = false;
  while (true) {
    x = rand()%(width/blockSize) * blockSize;
    y = rand()%(height/blockSize) * blockSize;

    for (int i = 0; i < snakeLength; ++i) {
      if (x == snakePosition[i][0] && y == snakePosition[i][1]) {
	flag = true;
	break;
      }
    }

    if (!flag) break;
  }
}

Fruit::Fruit() {
  while (true) {
    x = rand()%(width/blockSize) * blockSize;
    y = rand()%(height/blockSize) * blockSize;

    if (!checkSnakeOverlap(snake)) {
      break;
    }
  }


}

int Fruit::getX() {
  return x;
}

int Fruit::getY() {
  return y;
}

void Fruit::reGenerate() {
  while (true) {
    x = rand()%(width/blockSize) * blockSize;
    y = rand()%(height/blockSize) * blockSize;

    if (!checkSnakeOverlap(snake) && !checkObstacleOverlap(obstacle)) {
      break;
    }
  }

}

bool Fruit::checkSnakeOverlap(Snake &snake) {
  vector <vector <int> > snakePosition = snake.getPosition();
  int snakeLength = snakePosition.size();

  for (int i = 0; i < snakeLength; ++i) {
    if (x == snakePosition[i][0] && y == snakePosition[i][1]) {
      return true;
    }
  }
  return false;
}

bool Fruit::checkObstacleOverlap(Obstacle &obstacle) {
  vector <vector <int> > obstaclePosition = obstacle.getObstacles();
  int obstacleLength = obstaclePosition.size();

  for (int i = 0; i < obstacleLength; ++i) {
    if (x == obstaclePosition[i][0] && y == obstaclePosition[i][1]) {
      return true;
    }
  }
  return false;
}



void Snake::paint(XInfo &xinfo) {
  XDrawArc(xinfo.display, xinfo.pixmap, xinfo.gc[0], position[0][0] + blockSize/4, position[0][1] + blockSize/4, blockSize/2, blockSize/2, 0, 360 * 64);
  int num_blocks = position.size();
  for (int i = 0; i < num_blocks; ++i) {
    XDrawRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], position[i][0], position[i][1], blockSize, blockSize);
  }
}

void Snake::restart() {
  speed = snakespeed;
  direction = "east";
  newDirection = "";
  blockCounter = 0;

  int length = position.size();
  for (int i = 0; i < length; ++i) {
    position.pop_back();
  }

  vector <int> startingPoint;
  vector <int> secondPoint;
  vector <int> thirdPoint;
  startingPoint.push_back(x);
  startingPoint.push_back(y);
  secondPoint.push_back(x-blockSize);
  secondPoint.push_back(y);
  thirdPoint.push_back(x-blockSize * 2);
  thirdPoint.push_back(y);
  position.push_back(startingPoint);
  position.push_back(secondPoint);
  position.push_back(thirdPoint);
}

void Snake::move(XInfo &xinfo) {
  if ((newDirection == "south" && direction != "north") ||
      (newDirection == "north" && direction != "south") ||
      (newDirection == "east" && direction != "west") ||
      (newDirection == "west" && direction != "east")) {
    direction = newDirection;
  }
  newDirection = "";

  blockCounter += speed;
  vector <int> firstpos;
  if (direction == "south") {
    if (blockCounter >= blockSize) {
      firstpos.push_back(position[0][0]);
      firstpos.push_back(position[0][1] + blockSize);
    }
  } else if (direction == "north") {
    if (blockCounter >= blockSize) {
      firstpos.push_back(position[0][0]);
      firstpos.push_back(position[0][1] - blockSize);
    }
  } else if (direction == "east") {
    if (blockCounter >= blockSize) {
      firstpos.push_back(position[0][0] + blockSize);
      firstpos.push_back(position[0][1]);
    }
  } else if (direction == "west") {
    if (blockCounter >= blockSize) {
      firstpos.push_back(position[0][0] - blockSize);
      firstpos.push_back(position[0][1]);
    }
  }
  if (blockCounter >= blockSize) {
    if (firstpos[0] < 0 || firstpos[0] > width || firstpos[1] < 0 || firstpos[1] > height) {
      GameOver = true;
    }
    position.insert(position.begin(), firstpos);
    position.pop_back();
    blockCounter -= blockSize;

  }
}

bool Snake::didHitInvincibility(Invincibility *invincibility) {
  int invX = invincibility->getX();
  int invY = invincibility->getY();

  if (position[0][0] == invX && position[0][1] == invY) {
    return true;
  } else {
    return false;
  }
}

bool Snake::didEatFruit(Fruit *fruit) {
  int fruitX = fruit->getX();
  int fruitY = fruit->getY();

  if (position[0][0] == fruitX && position[0][1] == fruitY) {
    return true;
  } else {
    return false;
  }
}

void Snake::EatingFruit() {
  int snakeLength = position.size();
  vector <int> lastPosition = position[snakeLength-1];
  vector <int> secondLastPosition = position[snakeLength-2];
  vector <int> newPosition;

  int lastX = lastPosition[0];
  int lastY = lastPosition[1];
  int secondLastX = secondLastPosition[0];
  int secondLastY = secondLastPosition[1];

  if (lastX == secondLastX && lastY == secondLastY + blockSize) {
    newPosition.push_back(lastX);
    newPosition.push_back(lastY + blockSize);
  } else if (lastX == secondLastX && lastY == secondLastY - blockSize) {
    newPosition.push_back(lastX);
    newPosition.push_back(lastY - blockSize);
  } else if (lastY == secondLastY && lastX == secondLastX + blockSize) {
    newPosition.push_back(lastX + blockSize);
    newPosition.push_back(lastY);
  } else if (lastY == secondLastY && lastX == secondLastX - blockSize) {
    newPosition.push_back(lastX - blockSize);
    newPosition.push_back(lastY);
  }

  position.push_back(newPosition);
}

bool Snake::didHitObstacle(vector <vector <int> > *obstacles) {
  int length = obstacles->size();

  for (int i = 0; i < length; ++i) {
    if (position[0][0] == (*obstacles)[i][0] && position[0][1] == (*obstacles)[i][1]) {
      return true;
    }
  }
  return false;
}

Snake::Snake(int x, int y): x(x), y(y) {
  speed = snakespeed;
  direction = "east";
  newDirection = "";
  blockCounter = 0;

  vector <int> startingPoint;
  vector <int> secondPoint;
  vector <int> thirdPoint;

  startingPoint.push_back(x);
  startingPoint.push_back(y);
  secondPoint.push_back(x-blockSize);
  secondPoint.push_back(y);
  thirdPoint.push_back(x-blockSize*2);
  thirdPoint.push_back(y);

  position.push_back(startingPoint);
  position.push_back(secondPoint);
  position.push_back(thirdPoint);
}

bool Snake::didEatItself() {
  int numBlock = position.size();
  for (int i = 1; i < numBlock; ++i) {
    if (position[i][0] == position[0][0] && position[i][1] == position[0][1]) {
      return true;
    }
  }
  return false;
}

void Snake::setNewDirection(string direction) {
  newDirection = direction;
}

int Snake::getSpeed() {
  return speed;
}

vector <vector <int> > Snake::getPosition() {
  return position;
}



>>>>>>> d6e3ff51e286dc507d30a4fd2cb6a9910167fdc2


/*
 * Initialize X and create a window
 */
void initX(int argc, char *argv[], XInfo &xInfo) {
<<<<<<< HEAD
	XSizeHints hints;
	unsigned long white, black;

   /*
	* Display opening uses the DISPLAY	environment variable.
	* It can go wrong if DISPLAY isn't set, or you don't have permission.
	*/	
	xInfo.display = XOpenDisplay( "" );
	if ( !xInfo.display )	{
		error( "Can't open display." );
	}
	
   /*
	* Find out some things about the display you're using.
	*/
	xInfo.screen = DefaultScreen( xInfo.display );

	white = XWhitePixel( xInfo.display, xInfo.screen );
	black = XBlackPixel( xInfo.display, xInfo.screen );

	hints.x = 100;
	hints.y = 100;
	hints.width = 800;
	hints.height = 600;
	hints.flags = PPosition | PSize;

	xInfo.window = XCreateSimpleWindow( 
		xInfo.display,				// display where window appears
		DefaultRootWindow( xInfo.display ), // window's parent in window tree
		hints.x, hints.y,			// upper left corner location
		hints.width, hints.height,	// size of the window
		Border,						// width of window's border
		black,						// window border colour
		white );					// window background colour
		
	XSetStandardProperties(
		xInfo.display,		// display containing the window
		xInfo.window,		// window whose properties are set
		"animation",		// window's title
		"Animate",			// icon's title
		None,				// pixmap for the icon
		argv, argc,			// applications command line args
		&hints );			// size hints for the window

	/* 
	 * Create Graphics Contexts
	 */
	int i = 0;
	xInfo.gc[i] = XCreateGC(xInfo.display, xInfo.window, 0, 0);
	XSetForeground(xInfo.display, xInfo.gc[i], BlackPixel(xInfo.display, xInfo.screen));
	XSetBackground(xInfo.display, xInfo.gc[i], WhitePixel(xInfo.display, xInfo.screen));
	XSetFillStyle(xInfo.display, xInfo.gc[i], FillSolid);
	XSetLineAttributes(xInfo.display, xInfo.gc[i],
	                     1, LineSolid, CapButt, JoinRound);

	XSelectInput(xInfo.display, xInfo.window, 
		ButtonPressMask | KeyPressMask | 
		PointerMotionMask | 
		EnterWindowMask | LeaveWindowMask |
		StructureNotifyMask);  // for resize events

	/*
	 * Put the window on the screen.
	 */
	XMapRaised( xInfo.display, xInfo.window );
	XFlush(xInfo.display);
=======
  XSizeHints hints;
  unsigned long white, black;

  /*
   * Display opening uses the DISPLAY	environment variable.
   * It can go wrong if DISPLAY isn't set, or you don't have permission.
   */	
  xInfo.display = XOpenDisplay( "" );
  if ( !xInfo.display )	{
    error( "Can't open display." );
  }

  /*
   * Find out some things about the display you're using.
   */
  xInfo.screen = DefaultScreen( xInfo.display );

  white = XWhitePixel( xInfo.display, xInfo.screen );
  black = XBlackPixel( xInfo.display, xInfo.screen );

  hints.x = 100;
  hints.y = 100;
  hints.width = 800;
  hints.height = 600;
  hints.flags = PPosition | PSize;

  xInfo.window = XCreateSimpleWindow( 
      xInfo.display,				// display where window appears
      DefaultRootWindow( xInfo.display ), // window's parent in window tree
      hints.x, hints.y,			// upper left corner location
      hints.width, hints.height,	// size of the window
      Border,						// width of window's border
      black,						// window border colour
      white );					// window background colour

  XSetStandardProperties(
      xInfo.display,		// display containing the window
      xInfo.window,		// window whose properties are set
      "animation",		// window's title
      "Animate",			// icon's title
      None,				// pixmap for the icon
      argv, argc,			// applications command line args
      &hints );			// size hints for the window

  /* 
   * Create Graphics Contexts
   */
  int i = 0;
  xInfo.gc[i] = XCreateGC(xInfo.display, xInfo.window, 0, 0);
  XSetForeground(xInfo.display, xInfo.gc[i], BlackPixel(xInfo.display, xInfo.screen));
  XSetBackground(xInfo.display, xInfo.gc[i], WhitePixel(xInfo.display, xInfo.screen));
  XSetFillStyle(xInfo.display, xInfo.gc[i], FillSolid);
  XSetLineAttributes(xInfo.display, xInfo.gc[i],
      1, LineSolid, CapButt, JoinRound);

  XSelectInput(xInfo.display, xInfo.window, 
      ButtonPressMask | KeyPressMask | 
      PointerMotionMask | 
      EnterWindowMask | LeaveWindowMask |
      StructureNotifyMask);  // for resize events

  /*
   * Put the window on the screen.
   */
  
  int depth = DefaultDepth(xInfo.display, DefaultScreen(xInfo.display));
  xInfo.pixmap = XCreatePixmap(xInfo.display, xInfo.window, width, height, depth);
  XMapRaised( xInfo.display, xInfo.window );
  XFlush(xInfo.display);
>>>>>>> d6e3ff51e286dc507d30a4fd2cb6a9910167fdc2
}

/*
 * Function to repaint a display list
 */
void repaint( XInfo &xinfo) {
<<<<<<< HEAD
	list<Displayable *>::const_iterator begin = dList.begin();
	list<Displayable *>::const_iterator end = dList.end();

	XClearWindow( xinfo.display, xinfo.window );
	
	// get height and width of window (might have changed since last repaint)

	XWindowAttributes windowInfo;
	XGetWindowAttributes(xinfo.display, xinfo.window, &windowInfo);
	unsigned int height = windowInfo.height;
	unsigned int width = windowInfo.width;

	// big black rectangle to clear background
    
	// draw display list
	while( begin != end ) {
		Displayable *d = *begin;
		d->paint(xinfo);
		begin++;
	}
	XFlush( xinfo.display );
}

void handleKeyPress(XInfo &xinfo, XEvent &event) {
	KeySym key;
	char text[BufferSize];
	
	/*
	 * Exit when 'q' is typed.
	 * This is a simplified approach that does NOT use localization.
	 */
	int i = XLookupString( 
		(XKeyEvent *)&event, 	// the keyboard event
		text, 					// buffer when text will be written
		BufferSize, 			// size of the text buffer
		&key, 					// workstation-independent key symbol
		NULL );					// pointer to a composeStatus structure (unused)
	if ( i == 1) {
		printf("Got key press -- %c\n", text[0]);
		if (text[0] == 'q') {
			error("Terminating normally.");
		}
	}
}

void handleAnimation(XInfo &xinfo, int inside) {
    /*
     * ADD YOUR OWN LOGIC
     * This method handles animation for different objects on the screen and readies the next frame before the screen is re-painted.
     */ 
	snake.move(xinfo);
=======
  list<Displayable *>::const_iterator begin = dList.begin();
  list<Displayable *>::const_iterator end = dList.end();

  // get height and width of window (might have changed since last repaint)

  XWindowAttributes windowInfo;
  XGetWindowAttributes(xinfo.display, xinfo.window, &windowInfo);
  unsigned int height = windowInfo.height;
  unsigned int width = windowInfo.width;

  XSetForeground(xinfo.display, xinfo.gc[0], WhitePixel(xinfo.display, DefaultScreen(xinfo.display)));  
  XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], 0, 0, width, height);
  XSetForeground(xinfo.display, xinfo.gc[0], BlackPixel(xinfo.display, DefaultScreen(xinfo.display)));  
  // big black rectangle to clear background

  // load a larger font
  XFontStruct * font;
  font = XLoadQueryFont(xinfo.display, "12x24");
  XSetFont (xinfo.display, xinfo.gc[0], font->fid);


  if (countInvincibility > 300) {
    flagInv = false;
    countInvincibility = 0;
    invincibility = Invincibility();
    dList.push_front(&invincibility);
  }

  if (startGame) {
    string welcome = "Welcome to Snake!";
    string start = "To Start the Game, please press G.";
    string name = "Name: Yuxuan He";
    string userid = "userid: y254he";

    XDrawImageString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 200, 150, welcome.c_str(), welcome.length());
    XDrawImageString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 200, 200, start.c_str(), start.length());
    XDrawImageString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 50, 550, name.c_str(), name.length());
    XDrawImageString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 50, 575, userid.c_str(), userid.length());

    vector <string> description;
    description.push_back("How to Play:");
    description.push_back("Use WASD to control your snake.");
    description.push_back("To pause, press P.");
    description.push_back("To resume, press R.");
    description.push_back("To start a new game, press N.");
    description.push_back("To quit, press Q.");
    description.push_back("Eat fruit to get score.");
    description.push_back("Do not hit wall, obstacles");
    description.push_back("  or yourself.");


    int pos = 300;
    int descriptionLength = description.size();
    for (int i = 0; i < descriptionLength; ++i) {
      XDrawImageString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 400, pos, description[i].c_str(),description[i].length());
      pos += 30;
    }
  } else if (GameOver) {
    string gameover = "GAME OVER!";
    string scoreline = "Your score: " + score.getScoreString();
    string restartline = "To restart the game, please press N.";
    string quitline = "To quit, please press Q.";

    XDrawImageString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 200, 150, gameover.c_str(), gameover.length());
    XDrawImageString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 200, 200, scoreline.c_str(), scoreline.length());
    XDrawImageString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 250, 350, restartline.c_str(), restartline.length());
    XDrawImageString(xinfo.display, xinfo.pixmap, xinfo.gc[0], 250, 400, quitline.c_str(), quitline.length());
  } else {

    // draw display list
    while( begin != end ) {
      Displayable *d = *begin;
      d->paint(xinfo);
      begin++;
    }
  }
  XCopyArea(xinfo.display, xinfo.pixmap, xinfo.window, xinfo.gc[0], 0, 0, width, height, 0, 0);
  XFlush( xinfo.display );
}

void handleKeyPress(XInfo &xinfo, XEvent &event) {
  KeySym key;
  char text[BufferSize];

  /*
   * Exit when 'q' is typed.
   * This is a simplified approach that does NOT use localization.
   */
  int i = XLookupString( 
      (XKeyEvent *)&event, 	// the keyboard event
      text, 					// buffer when text will be written
      BufferSize, 			// size of the text buffer
      &key, 					// workstation-independent key symbol
      NULL );					// pointer to a composeStatus structure (unused)
  if ( i == 1) {
    printf("Got key press -- %c\n", text[0]);

    if (!startGame) {
      if (text[0] == 'p') {
	pauseFlag = true;
      } else if (text[0] == 'r') {
	pauseFlag = false;
      } else if (text[0] == 'n') {
	if (GameOver == true) {
	  GameOver = false;
	}
	fruit.restart();
	snake.restart();
	obstacle.restart();
	score.restart();
	restartFlag = true;
	pauseFlag = false;
      }
    }
    if (text[0] == 'q') {
      error("Terminating normally.");
    } else if (text[0] == 'g' && startGame == true) {
      startGame = false;
    }

    if (!pauseFlag && !startGame) {
      if (text[0] == 'w') {
	snake.setNewDirection("north");
      } else if (text[0] == 's') {
	snake.setNewDirection("south");
      } else if (text[0] == 'a') {
	snake.setNewDirection("west");
      } else if (text[0] == 'd') {
	snake.setNewDirection("east");
      }
    }
  }
}

void handleAnimation(XInfo &xinfo, int inside) {
  if (!startGame) {
    snake.move(xinfo);
    if (snake.didEatFruit(&fruit)) {
      snake.EatingFruit();
      fruit.reGenerate();
      score.updateScore();

      score.convertString();
    }
    if (!flagInv) {
      if (snake.didEatItself()) {
	GameOver = true;
      }
      vector <vector <int> > obstacles = obstacle.getObstacles();
      if (snake.didHitObstacle(&obstacles)) {
	GameOver = true;
      }
      if (snake.didHitInvincibility(&invincibility)) {
	countInvincibility++;
	flagInv = true;
	dList.erase(dList.begin());
      }
    } else {
      countInvincibility++;
    }
  }
>>>>>>> d6e3ff51e286dc507d30a4fd2cb6a9910167fdc2
}

// get microseconds
unsigned long now() {
<<<<<<< HEAD
	timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

void eventLoop(XInfo &xinfo) {
	// Add stuff to paint to the display list
	dList.push_front(&snake);
    dList.push_front(&fruit);
	
	XEvent event;
	unsigned long lastRepaint = 0;
	int inside = 0;

	while( true ) {
		/*
		 * This is NOT a performant event loop!  
		 * It needs help!
		 */
		
		if (XPending(xinfo.display) > 0) {
			XNextEvent( xinfo.display, &event );
			cout << "event.type=" << event.type << "\n";
			switch( event.type ) {
				case KeyPress:
					handleKeyPress(xinfo, event);
					break;
				case EnterNotify:
					inside = 1;
					break;
				case LeaveNotify:
					inside = 0;
					break;
			}
		} 

		usleep(1000000/FPS);
		handleAnimation(xinfo, inside);
		repaint(xinfo);
	}
=======
  timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000000 + tv.tv_usec;
}

void eventLoop(XInfo &xinfo) {
  dList.push_front(&snake);
  dList.push_front(&score);
  dList.push_front(&fruit);
  dList.push_front(&obstacle);
  dList.push_front(&invincibility);

  XEvent event;
  unsigned long lastRepaint = 0;
  int inside = 0;

  while( true ) {

    if (XPending(xinfo.display) > 0) {
      XNextEvent( xinfo.display, &event );
      cout << "event.type=" << event.type << "\n";
      switch( event.type ) {
	case KeyPress:
	  handleKeyPress(xinfo, event);
	  break;
	case EnterNotify:
	  inside = 1;
	  break;
	case LeaveNotify:
	  inside = 0;
	  break;
      }
    }

    if (!pauseFlag || restartFlag) {

      restartFlag = false;

      unsigned long end = now();

      if (end - lastRepaint > 1000000/FPS) {
	handleAnimation(xinfo, inside);
	repaint(xinfo);
	lastRepaint = now();
      }
    }
  }

>>>>>>> d6e3ff51e286dc507d30a4fd2cb6a9910167fdc2
}


/*
 * Start executing here.
 *	 First initialize window.
 *	 Next loop responding to events.
 *	 Exit forcing window manager to clean up - cheesy, but easy.
 */
int main ( int argc, char *argv[] ) {
<<<<<<< HEAD
	XInfo xInfo;

	initX(argc, argv, xInfo);
	eventLoop(xInfo);
	XCloseDisplay(xInfo.display);
=======
  if (argc == 3) {
    stringstream con1(argv[1]);
    stringstream con2(argv[2]);

    con1 >> FPS;
    con2 >> snakespeed;
    snake = Snake(100,450);
  }
  XInfo xInfo;

  initX(argc, argv, xInfo);
  eventLoop(xInfo);
  XCloseDisplay(xInfo.display);
>>>>>>> d6e3ff51e286dc507d30a4fd2cb6a9910167fdc2
}
