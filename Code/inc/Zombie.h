#ifndef _Zombie_H
#define _Zombie_H

#include "Organism.h"
#include "Human.h"


class Zombie : public Organism
{
protected:
    int starveCount = 1;
public:
	Zombie();
	Zombie(City *city, int width, int height );
	virtual ~Zombie();

	virtual void move();

};

#endif
