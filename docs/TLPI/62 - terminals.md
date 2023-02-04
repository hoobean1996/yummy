# terminals
historically, users uses a UNIX system using a termnial connected via a serial line.
Termnials were `cathode ray tubes CRT`, typically CRTs 24 lines by 80 columns.

The usual interface to modern UNIX systems is an `X Window System` window manager on a high performance bit-mapped graphical monitor.

Both a conventional terminal and a terminal emulator have an associated terminal driver that handles input and output on the device.

Terminal Emulator -> Pseudoterminal

The Driver has two modes:
  - `Canonical mode`: terminal input is processed line by line, and line editing is enabled.
  - `Noncanonical mode`: terminal input is not gathered into lines.

The terminal driver also interprets a range of special characters, for `interrupt` character, and `end-of-file` character. such interpreation may result in a signal beging generated for the fore-ground process group.


## retrieving and modifying terminal attributes

```c++
#include <termios.h>

int tcgetattr(int fd, struct termios *termios_p);

int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);


struct termios {
  tcflag_t c_iflag; // input
  tcflag_t c_oflag; // output
  tcflag_t c_cflag; // control
  tcflag_t c_lflag; // local modes
  cc_t c_line;    // line discipline
  cc_t c_cc[NCCS];  // terminal special character
  speed_t c_ispeed; // input speed
  speed_t c_ospeed; // output speed
}; 
```


## stty
the stty command is the command line analog of the `tcgetattr` and `tcsetattr` functions.

