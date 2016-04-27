#ifndef CTIRETTE_H
#define CTIRETTE_H


class CTirette
{
    public:
        CTirette();
        virtual ~CTirette();
        void initTirette();
        bool etat();
        void printEtat();
    protected:
    private:
    int m_Tpin;
   
};

#endif // CTIRETTE_H
