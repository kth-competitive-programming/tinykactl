%!
/size 15 def
/r 20 def
size size scale
1 size div setlinewidth
-1 -2 moveto
/e 3 def
r 3 mul {
  e 3 sqrt rmoveto
  r {
    1 3 sqrt rlineto
    2 0 rlineto
    1 3 sqrt neg rlineto
    false { %Trigrid
      -4 0 rlineto
      1 3 sqrt neg rmoveto
      2 3 sqrt 2 mul rlineto
      -2 0 rmoveto
      2 3 sqrt -2 mul rlineto
      1 3 sqrt rmoveto
    } if
    2 0 rmoveto
  } repeat
  r -6 mul 0 rmoveto
  /e e neg def
} repeat
stroke
showpage
