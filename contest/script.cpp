mkdir data  #  done done/data

echo 'bc++ -q -lq -e$1 $1.cpp' > c

echo 'cat > data/$1_$2.in' > i

echo 'cat > data/$1_$2.ans' > o

echo 'cp data/$1_$2.in $1.in; ./$1 | tee data/$1_$2.out' > t

echo 'cat > $1.in; ./$1 | tee data/$1_$2.out' > td

echo 'diff data/$1_$2.out data/$1_$2.ans' > d

echo 'a2ps $1.cpp' > p


chmod +x c i o t td d p  #  submit n f


#echo 'bc++ -q -lq -O2 -w-par- -w-pia- -w-ovf- -e$1 $1.cpp' > c

#echo 'g++ -Wall -o $1 $1.cpp' > c
#echo './$1 < data/$1_$2.in | tee data/$1_$2.out' > t
#echo './$1 | tee data/$1_$2.out' > td
#echo 'mail judge@... < $1.cpp' > submit
#echo 'cp ../Template.cpp $1.cpp' > n
#echo 'mv $1* done; mv data/$1* done/data' > f
