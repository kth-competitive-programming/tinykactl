mkdir data  #  done done/data

echo 'g++ -Wall -o $1 $1.cc' > c

echo 'cat > data/$1_$2.in' > i

echo 'cat > data/$1_$2.ans' > o

echo './$1 < data/$1_$2.in | tee data/$1_$2.out' > t

echo './$1 | tee data/$1_$2.out' > td

echo 'diff data/$1_$2.out data/$1_$2.ans' > d

echo 'a2ps --line-numbers=1 $1.cpp' > p

echo 'submit $1.cc' > submit

echo 'cp Template.cpp $1.cc' > n

#echo 'mv $1* done; mv data/$1* done/data' > f

chmod +x c i o t td d p  #  submit n f

