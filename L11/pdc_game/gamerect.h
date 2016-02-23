#ifndef GAMERECT_H
#define GAMERECT_H


class GameRect
{
    public:
        GameRect();
        virtual ~GameRect();
        GameRect(const GameRect& other);
        GameRect& operator=(const GameRect& other);
        int getWidth() { return m_Width; }
        int getHeight() { return m_Height; }
        int getX() { return m_X; }
        int getY() { return m_Y; }
        int getColor() { return m_Color; }
        char getChar() {return m_Char; }
        void setWidth(int val) { m_Width = val; }
        void setHeight(int val) { m_Height = val; }
        void setX(int val) { m_X = val; }
        void setY(int val) { m_Y = val; }
        void setColor(int val) { m_Color = val; }
        void setChar(char val) { m_Char = val; }

        void drawStep(int stepNumber);
        void drawRect();
        int stepsCount(void);
    protected:
    private:
        enum RectSide{
            RCT_LEFTTOP,
            RCT_TOP,
            RCT_RIGHTTOP,
            RCT_RIGHT,
            RCT_RIGHTBOTTOM,
            RCT_BOTTOM,
            RCT_LEFTBOTTOM,
            RCT_LEFT
        };
        RectSide getRectSideOffset(int step, int * offset);
        void getRectXY(int step, int * ret_x, int * ret_y);

        void refreshColor(void);
        int m_Width;
        int m_Height;
        int m_X;
        int m_Y;
        char m_Char;
        int m_Color;
};

#endif // GAMERECT_H
