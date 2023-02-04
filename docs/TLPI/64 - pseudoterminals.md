# pseudoterminals

A `Pseudoterminal` is a virtual device that provides an IPC channel.

on one end of the channel is a program that expects to be connected to a terminal device,
on the other end is a program that drives the terminal-oriented program by using the channel to send it input and read its ouput.

A pseudoterminal is a pair of connected virtual devices:
  - pseudoterminal master
  - pseudoterminal slave
bidirectional pipe - two process can open the master and slave and then transfer data in either directioin though the pseudoterminal.

The key point about a pseudoterminal is that the salve device appers just like a standard terminal.

All of the operations that can be applied to a terminal device can also be applied to a pseudoterminal slave device.


## how programs use pseudoterminals
1. the standard input, output, and error of the terminal-oriented program are connected to the `pty slave`.
2. `pty slave` is controlling the `terminal-oriendted` program.
3. on the other side of the `pty`, a driver program acts as a proxy for the user, supplying input to the terminal-oriented program and reading that program's output.
4. the `driver program` is simultaneously reading from and writing to another I/O channel. It is acting as a relay, passing data in both dirctions between the `pty` and another program.


steps:
1. the driver program open the pty master,
2. the driver program calls `fork` to create a child process,
   1. the child call `setsid` to start a new seccion, the child is session leader, the child would lose controlling terminal.
   2. open the pty slve device, since the child process is a session leader, and it doesn't have a controlling terminal, the pty slave becomes the controlling terminal.
   3. use `dup` to duplicate the file descriptor for the slave device on I/O, error
   4. call exec to start the terminal-oriented program that is to be connected to the pty slave.

## ssh
1. user at terminal -> terminal --> ssh client
2. ssh client  --> tcp/ip --> ssh server
3. ssh server (driver) --> pty master
4. pty master --> pty slave
5. pty slave --> login shell

## application of ptys
1. `expect` program use a pty to allow an interactive terminal oriented program to be driven from a script file
2. terminal emulator such as `xterm` employ pty to provide a terminal-related functionality that goes with a terminal window.
3. the `screen` program use pty to multiplex a single physical terminal between multiple process.
4. pseudoterminals are used in the `script` program, which records all of the input and output that occurs during a shell session



## open an unused master
```c++
#include <stdlib.h>
#include <fcntl.h>

int posix_openpt(int flags);
```

## change slave ownership and permission
```c++
#include <stdlib.h>
int granpt(int mfd);
```