#ifndef CSWITCH_H
#define CSWITCH_H

class CSwitch
{
    public:
        CSwitch();
        virtual ~CSwitch();
        void init();
        int color();

    protected:
    private:

    int m_pinA, m_pinB;
    int m_green, m_purple;
};

#endif // CSWITCH_H