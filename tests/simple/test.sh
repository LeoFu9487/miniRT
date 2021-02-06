cd ../../
make debug
for i in {00..09}
do
	./miniRT tests/simple/$i.rt && cat tests/simple/$i.rt &&  printf "\n \n \n \n \n \n \n"
done
