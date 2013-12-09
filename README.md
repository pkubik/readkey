readkey
=======

Unbuffered input.

Working only on Linux!

initReadKey() must be called before any other function.

int readKey(char* buff, unsigned int size)
Fills given buff array with an array of pressed keys. 
Note that some keys are represented as multiple characters.
The second parameter is number of read bytes (1 byte == 1 character), and should be lesser than the size of buff.
Returns negative error code or number of actually read bytes.

int awaitKey()
Simply waits for any key.
Return values as above.
