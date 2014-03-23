dev-wars-sith
=============

Code for 'dev-wars' @ Instruo 2014  
Problem: http://instruo.in/dw-sith.html  

Compilation:

The build system used is cmake.  
The given instructions assume an unix based OS.  
The available C++ compiler must support C++11.  
GCC 4.6.x will work, but 4.8+ is recommended.  
Recent clang versions will also be able to compile it.  

cd dev-wars-sith #root dir of the project  
mkdir build #Create a directory for the executable  
cd build  
cmake ..  
make  

To execute, in the build directory:
./dev-wars-sith #for interactive mode

Operation:  
There are two modes of operation:  
1. Interactive (./dev-wars-sith ) :  
  This mode provides a prompt the user is supposed to use.  
  The operations supported are:  
  1. load filename : File 'filename' containing the encrypted text is loaded.
  2. decrypt: Decrypts the file and displays the plaintext.
  3. graph: Shows a graph denoting the communication channels between the rebel bases.
  4. color: Shows the same graph, but numbers(traditionally called colors) are appended to them in such a way that no two adjacent base has the same color.
  5. rebuild (optional filename): Reconstructs the message in such a way that no two adjacent rebel bases recieve the same message. If a filename is provided, the text is re-encrypted and saved in the given file.
  6. help: Displays this message
  7. quit: Ends the application  
  Since the key words were carefully chosen to have unique first characters, 
  you can skip the rest of the string for brevity.  
  For example, "l a.txt" loads the file "a.txt"
    

2. Non-interactive:  
  This is mainly for testing purposes and can be used by giving the name of the input file as a command line argument.   The program dumps all its output into stdout for debugging purposes.

