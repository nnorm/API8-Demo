# API8-Demo
Demo for API8 inter-university demoparty.

## Description
This is the repository I used while making a demo for the event API8 in 2015. Its source code is ugly but it can serve as an exemple of how to make a small demo very quickly.
Since it was a few weeks project and was never touched again, this repository is archived.

## Rendering
All the rendering is done in a single pass, in a fragment shader. I used sphere tracing (aka raymarching) to render stuff on-screen.

## Dependencies
+ **GNU Rocket**: to synchronize audio and visuals.
+ **GLM**: OpenGL Mathematics, as the name suggest it's used for mathematic operations using a GLSL-like syntax.
+ **BASS**: audio file loading and playing.
+ **OpenGL**: graphics API.
+ **Assimp**: model loader, although it is not used in this project.
