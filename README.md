Obstacles: The Game
===

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

- The `-p80:80 option maps port 80 from the Docker container to ports on your host computer. This should allow you to go to http://localhost with your web browser and see the ENVIRO client. It should say "Enviro Error: No connection. Is the server running? See here for help." at this point.

- The -p8765:8765 option allows the ENVIRO client to communicate with the enviro server (not yet running) via a WebSocket.

- The command 'esm start' uses the enviro setup manager to start a web server from which your browser can access the ENVIRO client.

Execution
===

To run the game, type

```bash
cd obstacles
cd obstacle_course
make
enviro
```

Navigate to 'http://localhost'. The user should see the obstacle course at this point. 

To stop the enviro server, press 'Ctrl-C'.

How to Play
===

Player is controlled via the keyboard, via these keys:

- w: forward
- s: back
- a: right
- d: left
- spacebar: shoot bullets
