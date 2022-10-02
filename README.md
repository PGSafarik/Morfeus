# Morfeus - Universal GUI launcher for games and engines
-01.10.2022-

*Content:*
  1. [General info](#1-general-info)
  2. [Compilation and installation](#2-compilation-and-installation)
  3. [Known errors and bugs](#3-known-errors-and-bugs)
  4. [The project state and plans for the future](#4-project-state-and-plans-for-the-futhure)
  5. [Author and project licencion](#5-Author-and-project-licencion)
  6. [Internet](#6-internet)
  
<p align="center"><img src="docs/images/screenshot.png?raw=true" width="70%" />  

## 1. GENERAL INFO:
Many games provide the user with a special window before starting, with the help of which the behavior of the game itself can be changed. Here, the user (player) can choose from where and in what way the game can be started, or the possibility of configuration, the possibility of adapting the parameters of the hw game program on which it is running. That's why I use the presentation of the game itself. These small windows, often implemented as separate small applications, are generally called "launchers".

Unfortunately, there are a number of games, engines and simulators that would appreciate such a launcher. Or even a possible game creator could appreciate the existence of a launcher, to which he would only provide instructions, what to offer the user and how the option to sell the game alongside another program. And I created the Morfeus program exactly for these purposes. Morpheus was originally supposed to be an internal part of the Gorgon game manager project. However, it was separated into a separate project and is still being actively worked on.

Morfeus itself works by creating a launcher window and then loading an xml file (so-called control file) that contains all the necessary instructions to present the choices and options for launching the game to the user. The control file can be specified to morpheu in several ways. On the one hand, it can be stored in predefined system or user directories and then called only by the file name (without the extension), or it is possible to create a link to the morphea executable file and name it the same as the given control file. The trigger is then fired with one command. Another option is to specify the full path to the control file with the -f parameter.

Morpheus can also be used to launch several games at once, if necessary for the entire series. For example, if you want to create a trigger for the Legacy Of Kain series, which contains a total of five titles. For this purpose, Morfeus has so-called contexts, where each context represents one game title, defined right in the control file.

Morfus can display png images that can be used either as a vertical cover or as icons. It also contains icon theme managers (Oxygen, Gnome, Faenza, Adwaita). The icon theme is usually determined by the user, but it is possible to add and set your own theme. For all images, it is necessary to take into account the size at this moment. Cover should have maximum dimensions of 265 x 400, icons 16x16 - 32x32 max.

## 2. COMPILATION AND INSTALLATION:
*Dependecies:*
  * [Foxtoolkit 1.7.76](http://fox-toolkit.org/ftp/fox-1.7.76.tar.gz)
  * [FXGHI 0.2.1](https://github.com/PGSafarik/FoxGHI)
  * [TinyXML-2 8.0.0](https://github.com/leethomason/tinyxml2)
  
*Aditional dependencies for compilation:*
  * cmake >= 3.10
  * g++

  
After downloading the project from Github (and possibly unzipping it), go to the folder with the project and enter the following command sequence:
```
  mkdir build
  cd build 
  cmake .. && make
  sudo make install
```
After successfully compiling and building the project, the resulting program, including the Lua language launcher, 
will be installed in the directory /usr/local/bin

Note:
The foxlib library MUST be installed on your system at compile time. Version 1.7 is a development version, so it is possible that you will not have it on your system and it will not be available in the repository, so you will have to install it manually. More information on how to do this can be found on the foxtoolkit website. The following lines refer to any CMakeLists modifications.

If you have the library installed in a location other than the standard one, this fact must be entered in the CMakeLists.txt file in the project directory. Find and change the lines setting the library path:
```
    INCLUDE_DIRECTORIES( "/Cesta/vasi/instalaci/foxlib/include" )   #Foxlib headers
    LINK_DIRECTORIES( "/Cesta/vasi/instalaci/foxlib/lib" )          #Foxlib library
```
These lines are commented out by default, so remove the leading '#' characters after editing, and then save the file. Next, follow the instructions for building and installing the project above as normal.

## 3. KNOWN ERRORS AND BUGS
* 27/09/2022 - No load control file from CMD  - FIXED, CLOSED 30/09/2022  
  When entering (only) the name of the control file from CMD, Morfeus does not load it.  
  RESOLUTION: The error was in checking the name under which Morfeus was run. This led to the program mistakenly thinking it was running over a link.  
* 30/09/2022 - IconTheme no Load feanza.cfg  - FIXED, CLOSED 01/10/22  
  RESOLUTIN: The icon manager will be overwritten
  
## 4. PROJECT STATE AND PLANS FOR THE FUTHURE
Under construction


## 5. AUTHOR AND PROJECT LICENCION:
Copyright (C) 2019 - 2022 Pavel Šafařík <drakarax@seznam.cz>
All rights reseved.

This file is part of Morfeus.

Morfeus is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Morfeus is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the 
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Morfeus. If not, see 
<https://www.gnu.org/licenses/>.

## 6. INTERNET
  * [Author's blog (CZ)](http://bfuplusplus.blogspot.cz/)
  * [Gorgona](https://github.com/PGSafarik/Gorgona)

=== END ===
