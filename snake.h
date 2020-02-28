#include <vector>
#include <string>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

class Score;
class Fruit;
class Obstacle;
class Snake;

struct XInfo {
  Display	 *display;
  int		 screen;
  Window	 window;
  GC		 gc[3];
  int		width;		// size of window
  int		height;
  Pixmap        pixmap;
};



class Displayable {
  public:
    virtual void paint(XInfo &xinfo) = 0;
    virtual void restart() = 0;
};

class Invincibility : public Displayable {
  public:
    virtual void paint(XInfo &xinfo);

    virtual void restart();

    Invincibility();

    bool checkSnakeOverlap(Snake &snake);

    bool checkFruitOverlap(Fruit &fruit);

    bool checkObstacleOverlap(Obstacle &obstacle);

    int getX();

    int getY();


  private:
    int x;
    int y;
};

class Score : public Displayable {
  public:
    virtual void paint(XInfo &xinfo);

    virtual void restart();

    Score();

    void updateScore();

    void convertString();

    std::string getScoreString();


  private:
    int x;
    int y;
    int scoreNumber;
    std::string scoreNumberString;
};

class Obstacle : public Displayable {
  public:
    virtual void paint(XInfo &xinfo);

    virtual void restart();

    Obstacle();

    bool checkSnakeOverlap(int x, int y, Snake &snake);

    bool checkFruitOverlap(int x, int y, Fruit &fruit);

    std::vector <std::vector <int> > getObstacles();


  private:
    std::vector <std::vector <int> > position;
    int num_obstacles;
    int min_num_obstacles;
};

class Fruit : public Displayable {
  public:
    virtual void paint(XInfo &xinfo);
    virtual void restart();
    Fruit();

  int getX();

  int getY();

  void reGenerate();

  bool checkSnakeOverlap(Snake &snake);

  bool checkObstacleOverlap(Obstacle &obstacle);


private:
  int x;
  int y;
};      

class Snake : public Displayable {
public:
  virtual void paint(XInfo &xinfo);

  virtual void restart();

  void move(XInfo &xinfo);

  bool didHitInvincibility(Invincibility *invincibility);

  bool didEatFruit(Fruit *fruit);

  void EatingFruit();

  bool didHitObstacle(std::vector <std::vector <int> > *obstacles);

  Snake(int x, int y);

  bool didEatItself();

  void setNewDirection(std::string direction);

  int getSpeed();

  std::vector <std::vector <int> > getPosition();




private:
  int speed;
  std::vector <std::vector <int> > position;
  std::string direction;
  std::string newDirection;
  int x;
  int y;
  int blockCounter;
};
