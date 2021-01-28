# C-Resolver
- Simple Hosts Resolver Written In C Language.
- This Script Has Been Made For Linux Based Systems. To Use It On Windows You Need To Switch To Windows API To Use Socket.

## Installation
```
git clone https://github.com/DEMON1A/C-Resolver
cd C-Resolver/
./bin/resolver [FILE]
```

## How It Works?
- It's just a simple hosts resolver takes the first argument as the file that contains the hosts it should resolve. the program does read the hosts line by line and strip the new lines from it then get the host ip to perform the connection using it. after that it creates a connection to this host. if the connection is done with `-1` the code will print the domain on the screen until it's done. very simple.

- The code isn't that fast, so i don't recommend it to you in case you want something to use in the real world. if you know how to make it faster please create a pull request with it. i will be happy to know more about c since i'm stil learning it.

- The bin has been compiled using gcc with this command: `gcc resolved.c -o resolved`
