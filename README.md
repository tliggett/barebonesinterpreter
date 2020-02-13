# barebonesinterpreter
Interprets Bare Bones programming language

## Installation:
You must have make and gcc installed on your machine.

### Install make/gcc
#### OSX (Mac)
`brew install make`

`brew install gcc`
#### Linux
##### ubuntu/debian
`sudo apt install build-essential`
##### fedora
`yum groupinstall Development Tools'`

### Install barebones
`make barebones`

`sudo make install`


## Usage:

Bare Bones programming language consists of four statements:
* **clear:** initializes a variable and sets its value to 0
* **incr:** increments a variable by 1
* **decr:** decrements a variable by 1. If value of variable is 0, decr does nothing.
* **while:** runs commands in loop below
Additionally, there is an added **print** statement to print variable to screen which the interpreter will process.

### Interpreter Syntax
Statements are followed by the variable they are affecting.
Consider the following code example:

 ```
 clear x
 incr x
 decr x
 decr x
 incr x
 print x
 ```
The output of the program should be `x ==> 1`

### While Loops
Loops syntax is as follows:
```
while x
      decr x
      print x
      ;
```
The loop will interpret all statements before the break line `;` as a part of the loop.
