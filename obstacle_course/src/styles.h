#ifndef __VIRUS_STYLES__H
#define __VIRUS_STYLES__H

#include "enviro.h"

using namespace enviro;

//Defines the bullet's physical information. 
//This is called by player to define the bullets it shoots.
const json  BULLET_STYLE = 
                { 
                   {"fill", "green"}, 
                   {"stroke", "#888"}, 
                   {"strokeWidth", "2px"},
                   {"strokeOpacity", "0.25"}
                };

#endif