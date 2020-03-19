Obstacles: The Game
===

Overview
---
Obstacles is a one-player game in which a black robot, "Robot", must complete a course. There are multiple red obstacles, "Blocks", inside the course and the player controls a blue robot, "Player", to clear the path by shooting "Bullets" at the Blocks in order for the Robot to get through and reach the end. Robot is not user controlled and instead uses sensors to move through the course. 

Obstacles uses Elma and Enviro. Elma is an event loop and process for embedded and reactive systems. Enviro is a multi-agent, multi-user simulator environment. More information on Elma and Enviro can be found at the links below:

- [Elma](https://github.com/klavinslab/elma)
- [Enviro](https://github.com/klavinslab/enviro)

The source code for this project is available [on github](https://github.com/kcisne/obstacles).

Installation
===

Assuming the user has Git installed, do the following to install the code:

```bash
git clone https://github.com/kcisne/obstacles
```

From Dockerhub
===

Assuming the user has Docker installed, follow the instructions below:

To start the docker image environment with Enviro pre-loaded into it, do 

```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.61 bash
esm start
```

The above commands do the following:

- The `-p80:80` option maps port 80 from the Docker container to ports on your host computer. This should allow you to go to http://localhost with your web browser and see the ENVIRO client. It should say "Enviro Error: No connection. Is the server running? See here for help." at this point.

- The -p8765:8765 option allows the ENVIRO client to communicate with the enviro server (not yet running) via a WebSocket.

- The command `esm start` uses the enviro setup manager to start a web server from which your browser can access the ENVIRO client.

Execution
===

To run the game, type

```bash
cd obstacles
cd obstacle_course
make
enviro
```

Navigate to `http://localhost`. The user should see the obstacle course at this point. 

To stop the enviro server, press `Ctrl-C`.

How to Play
===

The user controls `Player` via the keyboard, via these keys:

- w: forward
- s: back
- a: right
- d: left
- spacebar: shoot bullets

The user must clear the path for `Robot`. If the path does not get cleared `Robot` will not be able to make it to the end. If `Robot` hits an obstacle and gets stuck, the user will need to restart the game. 

To restart the game, press `Ctrl-C`, then enter `enviro`.

Architecture
===

Statics
---

Obstacles contains statics for the walls, which form the course.
The position of the statics are defined in `config.json`.

Agents and References
---

Obstacles consists of 4 different agents:
- An agent called `Robot`: The file `defs/my_robot.json` contains information about the black robot in the game. This information dictates `Robot`'s shape and physical properties.
- An agent called `Player`: The file `defs/player.json` contains information about the blue robot in the game. This information dictates `Player`'s shape and physical properties.
- An agent called `Finish`: The file `defs/finish.json` contains information about the blue robot in the game. This information dictates `Finish`'s shape and physical properties.
- An agent called `Block`: The file `defs/block.json` contains information about the blue robot in the game. This information dictates Block's shape and physical properties.

All agent's are added in the project configuration file, `config.json`, where their positions are defined.

Obstacles also has 1 reference:
- A reference `Bullet`: The file `defs/bullet.json` contains information about the bullets being shot from the blue robot in the game. This information dictates `Bullet`'s shape and physical properties.

References are also added in the 'config.json' file.

Robot
---

The agent `Robot` is controlled by `robot.h`, which consists of 4 classes:

- `MovingForward`: State, which moves `Robot` forward when Robot is at angles `0`, `90`, `-90`.
- `Rotate`: State, which rotates Robot when `Robot`'s sensors detect a wall ahead. Robot will rotate to the side, which allows for the robot to contine moving. For example, if the robot reaches a wall and the sensor to the right detects enough space to continue down the path, then Robot will rotate to the right. 
- `MyRobotController`: StateMachine, which contains `Robot`'s initial state and transitions. `MovingForward` and `Rotate` emit events, which tell `Robot` which transition to make. 
- `MyRobot`: Declares the `Robot` class, inherits from Enviro, declares the constructor, and calls macro DECLARE_INTERFACE defined by enviro that sets up the shared library interface. The constructor must have exactly the type signature shown above, and must call the Agent constructor when it is initialized.

Player
---

The agent 'Player' is controlled by `player.h`, which consists of 2 classes:

- 'PlayerController': Process, which gives `Player` the ability to shoot bullets and to move when keys "w", "s", "a", "d", and "spacebar" are pressed. 
- 'Player': Declares the 'Player' class, inherits from Enviro, declares the constructor, and calls macro DECLARE_INTERFACE defined by enviro that sets up the shared library interface. The constructor must have exactly the type signature shown above, and must call the Agent constructor when it is initialized.

Describe how your project was designed, what choices you made, how things are organized, etc.

Finish
---

The agent `Finish` is controlled by `finish.h`, which consists of 2 classes:

- `finishController`: Process, which gives `Finish` (the green block at the end of the course) the ability to remove Robot from the game once Robot reaches the end of the course. (This implementation is still in work.)
- `finish`: Declares the `Finish` class, inherits from Enviro, declares the constructor, and calls macro DECLARE_INTERFACE defined by enviro that sets up the shared library interface. The constructor must have exactly the type signature shown above, and must call the Agent constructor when it is initialized.

Block
---

The agent `Block` is controlled by `block.h`, which consists of 2 classes:

- `blockController`: Process, which gives `Block` the ability to disappear when `Block` is hit by a bullet. 
- `block`: Declares the `Block` class, inherits from Enviro, declares the constructor, and calls macro DECLARE_INTERFACE defined by enviro that sets up the shared library interface. The constructor must have exactly the type signature shown above, and must call the Agent constructor when it is initialized.

Bullet
---

`Bullet` is controlled by `bullet.h`, which consists of 2 classes:

- `BulletController`: Process, which checks for `Bullet` collisions with `Block`. This process also removed `Bullet` after a few seconds.
- `Bullet`: Declares the `Bullet` class, inherits from Enviro, declares the constructor, and calls macro DECLARE_INTERFACE defined by enviro that sets up the shared library interface. The constructor must have exactly the type signature shown above, and must call the Agent constructor when it is initialized.


Results
===

Overall
---

I was able to get 'Robot' to navigate through the entire course without it being controlled by a user, which was my initial goal. I was also able to add a user-interface by adding a second robot, 'Player'. Overall, the results were positive and the agents do what they are supposed to do. 

Challenges
---

The main challenge with Obstacles that I encountered was getting `Robot` to navigate through the course without being controlled by a user. Having `Robot` rotate and move forward at the correct time was the most difficult part for me because I had to gather information on angle and sensor readings in order to give `Robot` the correct restrictions for each state. 

Future Improvements
---

The following are features that I plan to add:
- Have `Robot` disappear when it reaches the end of the course.
- Give the user the ability to restart the game without having to exit enviro.
- Add obstacles of different sizes and shapes, which require different amounts of bullets to be destroyed.
- Have `Robot` start movint only after the user moves `Player` first.

Acknowledgements
===

Thank you to Professor Eric Klavins and Victor Cannestro for providing guidance and mentoring throughout the quarter. 

References
===

- [Elma](https://github.com/klavinslab/elma)
- [Enviro](https://github.com/klavinslab/enviro)