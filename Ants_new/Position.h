#ifndef _POSITION_H_
#define _POSITION_H_
using namespace std;

class Position
{
private:
	int x;
	int y;
public:
	~Position();
	Position();
	Position(int x, int y);
	
	void setX(int x);
	void setY(int y);
	
	int getX();
	int getY();
	
};

#endif
