#ifndef REST_H
#define REST_H


class Rest //возможно будет виртуалка, смотри!!!
{
protected:
    int duration;
    bool dot;
public:
    Rest();
    Rest(int d);
    void basic(int d);
};

#endif // REST_H
