# Engine

This project is a try to replicate Cherno's game engine series ([https://youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT](https://youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT)) in Linux. We are bringing following changes from his implementation.

1.  CMAKE based build system for the project.
2.  Using Clang for compiling in Linux.
3.  Use smart pointers instead of raw pointers.

# Build and Run Instructions

## CMAKE

1.  Clone the repository with submodules 
 `$ git clone --recurse-submodules -j8 https://github.com/eshafeeqe/Engine.git cd Engine`
2. Create build folder
	`$ mkdir build`
3. Configure using CMAKE
	`$ cmake ..`
4. Build Project
	`$ make -j8`
5. Run application
	`$ ./../bin/Sandbox/Sandbox`
	
## Premake

1.  Clone the repository with submodules 
 `$ git clone --recurse-submodules -j8 https://github.com/eshafeeqe/Engine.git cd Engine`
3. Configure using Premake
	`$ premake5 gmake`
4. Build Project
	`$ make -j8`
5. Run application
	`$ ./bin/Debug-linux-x86_64/Sandbox/Sandbox`
