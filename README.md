---
cube2crypto: Scripting access for cube2 cryptography and authentication functions
---
By: Morgan Borman

License
----------------

This software is licensed under the terms of the Zlib license except where otherwise indicated.

Version
----------------
** 0.0.5 **

Current State
----------------
This is a work in progress. The only function that I have fully tested is _answerchallenge_. 
All the others may or may not generate the correct results at this time.

The next step is to create a test framework which can be used to proceed with fixing the issues
in a test driven manner.

What is it
----------------
A collection of functions pulled from the cube2 engine and wrapped for 
easy use in other projects which need to interface with cube2.


What can I use it for
----------------

Accessing cube2 cryptographic functions from the following languages

* C/C++
* Python (tested under Python 2.7)
* JavaScript (tested under Firefox 10.0.2 and Chrome 17.0.963.79)