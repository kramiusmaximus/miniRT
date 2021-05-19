# miniRT

## Introduction
miniRT is a raytracer application which visualizes basic shapes and implements a number of basic RT features as well as other nifty features. 

Shapes included:
- Triangle
- Square
- Sphere
- Plane
- Cyllinder

Features included:
- Reflectivity
- Transperancy
- Refraction
- Multiple Cameras
- Camera Movement
- Multithreaded Rendering
- Anti-aliasing
- In-app Screenshots (BMP format)
- Colored lights

## Installation
1. Clone this git repository.
2. Execute the command `make` in the root directory to compile the application.
3. Voila! You can now show off this mediocre raytracer application to your grandparents while they tell you about how easy you have it.

## Usage
This app is launched through the command line with additional arguments in the following way: `./miniRT {Path to scene} {optional '--save' argument}` e.g. `./miniRT ./scenes/vistavka1.rt`
This should launch a window displaying the rendered image of the scene provided. This repository already contains a few scenes that you can try out. Alternatively, you can make your own! See the 'Scene File Format' section for an overview of the scene file format.

### Scene File Format

### Controls
#### Camera Controls:
- WASD keys to move forward, left, back, and right.
- E/SPACE to go up/ down.
- Arrow keys to rotate the camera.
- M/N keys to switch to next/previous camera.
- B key to take a screen shot from the currently selected camera's perspective.

#### Other Feature Controls:
