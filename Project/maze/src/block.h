#ifndef __BLOCK_AGENT__H
#define __BLOCK_AGENT__H 

#include "enviro.h"

using namespace enviro;

class blockController : public Process, public AgentInterface {

    public:
    blockController() : Process(), AgentInterface(),  hit(false) {}

    void init() 
    {
        notice_collisions_with("Bullet", [&](Event &e) 
        {
            Agent& bullet = find_agent(e.value()["id"]);
            vx = bullet.velocity().x;
            vy = bullet.velocity().y;
            ignore_collisions_with("Bullet");
            hit = true;
        });          
    }

    void start() {}

    void pop() 
    {
        remove_agent(id());
    }    

    void update() 
    {
        if ( hit ) 
        {
            pop();
        } 
    }

    void stop() {}

    const int fmax = 100.0;
    bool hit;
    double vx, vy;

};

class block : public Agent {
    public:
    block(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    blockController c;
};

DECLARE_INTERFACE(block)

#endif