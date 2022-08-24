
New Wave Minidesk

![NEW WAVE MINIDESK ICONOGRAPHY, BLUE WAVES GRAY LEMON-LIME, and YELLOW PURPLE BOYD. Triplex Red arrow heading upwards set in small side of image](https://raw.githubusercontent.com/SamyBencherif/new-wave-minidesk/main/logo.png)

this EXPLORATION IN PERSONAL COMPUTER INTERACTION includes

(1) Custom deskop interface, launcher, and window management

(2) Interactive graphics programming format

(3) Window decorations

The most exciting part of this project is the graphics format. The desktop-windowing and editor features exist simply to give the format an excellent place to live. 

MDK graphics format aims to remove all parts of the program that you have to include for it to work but that don't contribute to your unique program's definition. MDK lets you focus on your program's meaning--rather than hinting how computers actually work via obligatory incantations all the time. MDK is turing complete.

### Sample MDK Program (drawing)

This 6 SLOC line MDK program is equivalent to 40 SLOC lines in CRaylib. It would be ~120 SLOC in many graphics programming environments.
```
mousedown:
  circles.push({x,y,r:10})

loop:
  background(WHITE)
  
  for circles:
    DrawCircle(x, y, r, BLACK)
```
### Unique features

- Arrays do not need to be declared or initialized... Just use them and the transpiler will detect it for you.
- Arrays are always of data structures, which are also defined by being used
- The for loop simply takes the name of an array as argument, and produces the contents of the data structure on each iteration.
- No nested structures... It simplifies my implementation, and after all is it truly an improvement to say object->position->x instead of object->x ?

#### Features from other languages

- Object (Data Structure) definitions can use both the name and value of variables. Meaning that {x,y} is the same as {x:x, y:y}
- Indent based flow is like Python, but I don't mind if you implement braces lol
- Specialized for loop is inspired by python `for (x,y,z) in vectorarray:` and javascript `for (var {x,y,z} of vectorarray)`.
- Graphics calls match CRaylib (structures in calls are flattened)
---

## Benchmark plans

(TODO compare to p5.js, native js, and shadertoy
which have been go-to's fastest ways to draft graphics programs)

(TODO also compare to pyraylib and pythonista(iOS))

(for fun, compare to TIC80, love2d, and pyxel)

(TODO in sea of todos, compare to non-competitve (in area of brevity) yet common graphics envs: JAVA AWT, Unity C# for 2D, SMFL, C OpenGL, WebGL, PyGame)

(also pyglet, which is pretty good for brevity)

( maybe someday benchmark against a super-optimized handwritten assembly GPU program ... 

or much more simply a SHADER PROGRAM compiled to metal with high speed uniform access (to mouse, key, and screeninfo).)

---

## Some stats

MDK uses circular arrays for everything, which makes it tolerant to endless entity spawning (it auto-deletes old ones) and resistant to memory leaks.

Launcher is compatible with native linux applications.

Window management features are compatible with EWMH/NetWM compliant 
window manager programs. NW minidesk does not manage windows by itself,
it adds functionality to existing compliant window managers (running on X11).

The interactive graphics format, called MDK, produces naitive linux applications using Raylib (which uses X11 and OpenGL).

## Windows / Mac / Non-POSIX

The desktop interface and launcher needs only ANSI C standard library and OpenGL and some kind of Windowing System (alternative to X11). This
part works easily on other platforms by adjusting the compliation routine.

The MDK format is currently defined by a transpiling program written in Python--which has a excellent cross platform support.

Window management, decorations can work for MDK programs across platforms, given the host OS supports window-less presentation and
client-window control.

---

## Installation

Install dependencies, and use the `make` command to create a local binary image.

## Run

Execute

`./program`

## Installation details

This program is built on raylib

Default compilation requires raylib installed to your system

If you prefer not to install to system, simply clone http://github.com/Raysan5/Raylib
into the directory of the program and modify the Makefile to use the local copy

to ensure all linker params work use 
-lX11
apt search x11
and sudo apt install libx11-dev <--- or something similar
