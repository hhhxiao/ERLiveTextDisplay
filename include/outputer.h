#ifndef OUTPUTER_H
#define OUTPUTER_H

#include <fstream>

class AbstractOutputer {
   public:
    virtual void update() = 0;
    virtual ~AbstractOutputer() {}
};

class TextOutputer : public AbstractOutputer {
   public:
    TextOutputer();
    virtual ~TextOutputer();

    virtual void update();

   private:
    std::ofstream f;
};
#endif
