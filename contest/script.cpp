echo 'g++ -ansi -Wall -o $1 $1.cc' > c
echo 'cat > $1.in' > i
echo 'cat > $1.ans' > o
echo 'diff $1.out $1.ans' > d
echo 'a2ps --line-numbers=1 $1' > p
echo 'cp Template.cc $1.cc' > n

chmod +x c i o d p n

