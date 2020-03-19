#ifndef __MY_ROBOT_AGENT__H
#define __MY_ROBOT_AGENT__H 

#include "enviro.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "math.h"

namespace
{
    using namespace enviro;

    class MovingForward : public State, public AgentInterface 
    {
        public:
        void entry(const Event& e) {}
        void during() 
        {
            /*
            If angle is 0, 90 or -90 degrees 
            (0, 1.57, -1.57 in radians),move forward.
            */
            if((angle() > 1.55 && angle() < 1.59) || (angle() > -0.05 && angle() < 0.05) || (angle() > -1.59 && angle() < -1.55))
            {
                track_velocity(6,0);
                /*
                If the robot reaches a wall 
                and has an opening on one side,
                then rotate.
                */
                if (sensor_value(0) < 20)
                {
                    if(sensor_value(3.14) > 25)
                    {
                        emit(Event(tick_name_rotate));
                        tick_name = tick_name_rotate;
                    } 
                    if(sensor_value(1.57) > 25)
                    {
                        emit(Event(tick_name_rotate));
                        tick_name = tick_name_rotate;
                    }     
                }
                else
                {
                    track_velocity(6,0);
                }                
            }
            else
            {
                emit(Event(tick_name_rotate));
                tick_name = tick_name_rotate;
            }
            
        }

        void exit(const Event& e) {}
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;
        std::string tick_name_rotate;
    };

    /*
    Defines when the robot will rotate to the right 
    and when it will rotate to the left.
    */
    class Rotate : public State, public AgentInterface 
    {
        public:
        void entry(const Event& e) {}
        void during() 
        {
            if(angle() > 1.5 && angle() < 1.6 && sensor_value(0) < 15)
            {
                track_velocity(0, 30*sin(0-angle()) - 300*angular_velocity());
            }
            else if(angle() > -0.5 && sensor_value(0) > 30 && sensor_value(3.14) > 30)
            {
                track_velocity(0, 30*sin(0-angle()) - 300*angular_velocity());
                emit(Event(tick_name_fwd));
                tick_name = tick_name_fwd; 
            }
            else if((angle() > -0.1 && angle() < 0.1) && sensor_value(0) < 20 && sensor_value(3.14) > 30)
            {
                track_velocity(0, 30*sin(-1.57-angle()) - 300*angular_velocity());
                emit(Event(tick_name_fwd));
                tick_name = tick_name_fwd;
            }
            else if(angle() < -0.7 && sensor_value(0) > 20 && sensor_value(3.14) > 30)
            {
                track_velocity(0, 30*sin(-1.57-angle()) - 300*angular_velocity());
                emit(Event(tick_name_fwd));
                tick_name = tick_name_fwd;
            }
            else if((angle() > -1.59 && angle() < -1.55) && sensor_value(0) < 15 && sensor_value(1.57) > 30 )
            {
                track_velocity(0, 30*sin(0-angle()) - 300*angular_velocity());
                emit(Event(tick_name_fwd));
                tick_name = tick_name_fwd;
            }
            else if((angle() > -1.4 && angle() < 0.01) && sensor_value(0) > 30 && sensor_value(1.57) > 30)
            {
                track_velocity(0, 30*sin(0-angle()) - 300*angular_velocity());
                emit(Event(tick_name_fwd));
                tick_name = tick_name_fwd;
            }
            else if((angle() > -0.1 && angle() < 0.1) && sensor_value(0) < 15 && sensor_value(1.57) > 30)
            {
                track_velocity(0, 30*sin(1.57-angle()) - 300*angular_velocity());
                emit(Event(tick_name_fwd));
                tick_name = tick_name_fwd;
            }
            else if(angle() > 0.3 && sensor_value(0) > 30 && sensor_value(1.57) > 30)
            {
                track_velocity(0, 30*sin(1.57-angle()) - 300*angular_velocity());
                emit(Event(tick_name_fwd));
                tick_name = tick_name_fwd;
            }
            else if((angle() > 1.55 && angle() < 1.59) && sensor_value(0) > 30 && sensor_value(1.57) < 15 && sensor_value(3.14) < 15)
            {
                track_velocity(0, 30*sin(1.57-angle()) - 300*angular_velocity());
                emit(Event(tick_name_fwd));
                tick_name = tick_name_fwd;
            }

        }

        void exit(const Event& e) {}
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name; 
        std::string tick_name_fwd;
    };

    class MyRobotController : public StateMachine, public AgentInterface 
    {
        public:
        //Define state machine initial state and transitions
        MyRobotController() : StateMachine() 
        {
            set_initial(move_forward); 
            tick_name = "tick_" + std::to_string(rand()%1000); // use an agent specific generated 
                                                               // event name in case there are 
                                                               // multiple instances of this class
            add_transition(tick_name_rotate, move_forward, rotate);
            add_transition(tick_name_fwd, rotate, move_forward);
        }

        void update() 
        {
            if ( rand() % 100 <= 5 ) 
            {
                emit(Event(tick_name));
            }   
            StateMachine::update();
        }

        MovingForward move_forward;
        Rotate rotate;
        std::string tick_name_rotate;
        std::string tick_name_fwd;
        std::string tick_name;
    };

    class MyRobot : public Agent 
    {
        public:
        MyRobot(json spec, World& world) : Agent(spec, world) 
        {
            add_process(c);
        }
        private:
        MyRobotController c;
    };
}

DECLARE_INTERFACE(MyRobot)

#endif