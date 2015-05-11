#About

Basic game in OpenGL and C++

Originally submitted as part of Trinity College coursework

This is an effort to rewrite the submitted project with the goals of making the code easier to read and run faster

#Requirements

To compile this project you must tell your compile to include the Include directory. 

Your compiler must also know where to find OpenGL, glew and GLFW libraries.

#Implemented features:

- User controllable avatar and camera

- Loading and displaying several textured models at once

- Multiple models can share the same vertex, UV and texture data, significantly saving on memory usage and loading times

- Simple physics

- Lighting

#Issues

Collision detection can sometimes fail and cause the player to get stuck in walls
