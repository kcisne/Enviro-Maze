#ifndef __FINISH_AGENT__H
#define __FINISH_AGENT__H 

#include "enviro.h"

using namespace enviro;

class finishController : public Process, public AgentInterface 
{

    public:
    finishController() : Process(), AgentInterface() {}

    void init() 
    {
        /*
        This is still in-work. Will define whether there is a collision with
        Robot and remove Robot when collision occurs.
        */
        notice_collisions_with("Robot", [&](Event &e) 
        {
            remove_agent(id());
        });
    }
    void start() {}

    void update() 
    {
        if ( counter++ > 20 ) 
        {
            remove_agent(id());
        }
    }

    void stop() {}

    double counter;

};

class finish : public Agent 
{
    public:
    finish(json spec, World& world) : Agent(spec, world) 
    {
        add_process(c);
    }
    private:
    finishController c;
};

DECLARE_INTERFACE(finish)

#endif