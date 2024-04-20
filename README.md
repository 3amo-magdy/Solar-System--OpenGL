# Solar System Project

## Introduction
The Solar System project is a visualization of the celestial bodies in our solar system using OpenGL. It includes the Sun, planets, moon, and Saturn's ring. The project allows for navigation and observation of the solar bodies.

-------------------
## YouTube Video
[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/EmEFZJJ1SzM/0.jpg)](https://www.youtube.com/watch?v=EmEFZJJ1SzM)

--------------
# Controls
- Navigation:
    - Move camera: WASD keys.
    - Rotate camera:
        - Up/Down: rotate around the x axis.
        - Left/Right: rotate around the z axis.
        - E/Q: rotate around the y axis.
    - Acceleration: Left-shift key (repeatedly pressed).
- Pause/resume animation: "P" key.
- Toggle orbits visibility: "O" key.
- Toggle fullscreen mode: "F" or F11 keys.
---------------

## Needed Libraries 

- **Freeglut**
- **Glew**
- **FreeImage**
---------------

# Project Modules & Classes

- ## Vec3
  - Represents a 3D vector with x, y, and z components.
  - Provides various vector operations such as addition, subtraction, scaling, normalization, cross product, magnitude, and dot product.

- ## Camera
  - Represents a camera in the 3D space.
  - Contains the camera position, view direction, up vector, and right vector.
  - Provides functions to move the camera in different directions and rotate it around the x, y, and z axes.

- ## CosmicSphere
  - Base class representing a cosmic sphere.
  - Contains properties such as radius, distance from the rotation target, rotation speed around the target, self-rotation speed, and texture.
  - Provides a `draw()` function to draw the cosmic sphere.

- ## Star
  - Derived class from `CosmicSphere` representing a star.
  - Contains additional properties such as the light source index and color.
  - Overrides the `draw()` function to draw the star.

- ## Ring
  - Derived class from `CosmicSphere` representing a ring around a planet.
  - Contains an additional property for the inner radius of the ring.
  - Overrides the `draw()` function to draw the ring.

----------------
## Some Implementation Details

### 1. Texture Loading:
  - The LoadTextureFromImg() function loads textures from image files using the FreeImage library.

### 2. Drawing Functions:
  - The draw() function of each cosmic sphere class handles drawing respective objects.
  - OpenGL functions are utilized to set material properties, bind textures, and draw geometries such as spheres, rings, and orbits.

### 3. Solar System Setup:
  - The solar system is initialized with the Sun and planets using the CosmicSphere class.
  - Each planet is positioned at a specific distance from the Sun and rotates around it at a certain speed.
  - The Moon orbits around the Earth, and the Saturn's ring is represented by the Ring class positioned around Saturn.
  - Every solar object rotates around itself with some velocity.
----------------
## References

- [Solar System Scope](https://www.solarsystemscope.com/textures/)
- [LearnOpenGL-Textures](https://learnopengl.com/Getting-started/Textures)
- [Stack Over Flow](https://stackoverflow.com/questions/17125843/how-do-i-load-textures-to-opengl-using-freeimage-library)

