echo 'g++ -Wall -o $1 $1.cc' > c
echo 'cat > $1.in' > i
echo 'cat > $1.ans' > o
echo './$1 < $1.in | tee $1.out' > t
echo './$1 | tee $1.out' > td
echo 'diff $1.out $1.ans' > d
echo 'a2ps --line-numbers=1 $1' > p
echo 'cp Template.cc $1.cc' > n

chmod +x c i o t td d p n

