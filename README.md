orion
=====

To configure SFML for VS 2012/13 follow http://www.youtube.com/watch?v=VcPRJE6Rt0o
Main changes: 
	Linker, General, Additional Libraries Directories : SFML/build/lib/Debug
	Linker, Input, Additional dependencies: sfml-graphics-d.lib
											sfml-window-d.lib
											sfml-system-d.lib
	C/C++, General, Additional include directories: SFML/SFML2.0/include
