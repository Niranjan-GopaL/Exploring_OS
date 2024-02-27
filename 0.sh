# Steps :-
# 1) chmod +x 0.sh
# 2) ./0.sh

cat globe.vt  | pv -q -L 6200
./animation.sh
make clean
make