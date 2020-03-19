Obstacles: The Game
===

Obstacles is a one-player game in which a robot must complete a course. There are multiple obstacles inside the course and the player must clear the path by shooting the obstacles in order for the robot to get through and reach the end. Obstacles uses Elma and Enviro. Elma is an event loop and process for embedded and reactive systems. Enviro is a multi-agent, multi-user simulator environment. More information on Elma and Enviro can be found in the links below:

- [Elma](https://github.com/klavinslab/elma)
- [Enviro](https://github.com/klavinslab/enviro)


From Dockerhub
===

To start the docker image environment, do 
```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.61 bash
```
This will start a bash prompt from which new projects can be built and the enviro server can be run. 