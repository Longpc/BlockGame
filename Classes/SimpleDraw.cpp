#include "SimpleDraw.h"

SimpleDraw* SimpleDraw::create()
{
	SimpleDraw* draw = new SimpleDraw();
	draw->autorelease();
	return draw;
}

SimpleDraw::SimpleDraw()
{
	m_lines = new std::vector<DrawLine>;
	m_points = new std::vector<DrawPoint>;
}

SimpleDraw::~SimpleDraw()
{
	delete m_lines;
	delete m_points;
}

void SimpleDraw::drawObject(void)
{
	int c = m_lines->size();
	for (int i = 0; i < c; i++)
	{
		DrawLine line = m_lines->at(i);
		//glColor4f(line.r, line.g, line.b, 1);
		DrawPrimitives::setDrawColor4F(line.r, line.g, line.b, 1);
		//        ccDrawLine(line.pt1, line.pt2);
		DrawPrimitives::drawLine(line.pt1, line.pt2);
	}

	c = m_points->size();
	for (int i = 0; i < c; i++)
	{
		DrawPoint pt = m_points->at(i);
		//glColor4f(pt.r, pt.g, pt.b, 1);
		DrawPrimitives::setDrawColor4F(pt.r, pt.g, pt.b, 1);
		//ccDrawPoint(pt.pt);
		DrawPrimitives::drawPoint(pt.pt);
	}
}