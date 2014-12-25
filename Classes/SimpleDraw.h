#include "cocos2d.h"

using namespace cocos2d;
typedef struct
{
	CCPoint pt1;
	CCPoint pt2;
	float r;
	float g;
	float b;
} DrawLine;

typedef struct
{
	CCPoint pt;
	float r;
	float g;
	float b;
} DrawPoint;

class SimpleDraw : public Node
{
public:
	static SimpleDraw* create();

	SimpleDraw();
	~SimpleDraw();
	virtual void drawObject(void);

	void appendLine(Point pt1, Point pt2, float r = 1, float g = 1, float b = 1);
	void appendPoint(float x, float y, float r = 1, float g = 1, float b = 1);
	void appendPoint(CCPoint pt, float r = 1, float g = 1, float b = 1);

private:
	std::vector<DrawLine>* m_lines;
	std::vector<DrawPoint>* m_points;
};