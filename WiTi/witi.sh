g++ -std=c++11 -pedantic -Wall -o witi witi.cpp
echo "1: "
./witi < dane1.txt
echo "poprawny:   131"

echo "2: "
./witi < dane2.txt
echo "poprawny:   502"

echo "3: "
./witi < dane3.txt
echo "poprawny:   279"

echo "4: "
./witi < dane4.txt
echo "poprawny:   66"

echo "5: "
./witi < dane5.txt
echo "poprawny:   267"

echo "6: "
./witi < dane6.txt
echo "poprawny:   57"

echo "7: "
./witi < dane7.txt
echo "poprawny:   1191"

echo "8: "
./witi < dane8.txt
echo "poprawny:   435"

echo "9: "
./witi < dane9.txt
echo "poprawny:   723"
