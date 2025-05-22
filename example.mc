int x
int y
mwrite "Enter a number:"
mread x
if ( x > 5 )
    mwrite "Number is greater than 5"
while ( x > 0 )
    mwrite x
    x = x - 1
    wait 500
for ( int y=0; | y<10 | y++ )
    mwrite y
mwrite "ASCII character for 65:"
cc ( 65 )
cascii
mwrite "→ Character mode activated"
int beeps
beeps = 3
mcuc ( beeps )
color red
mwrite "This is red text"
color 2
mwrite "This is color number 2"
wait 1000
mwrite "Program complete!"
