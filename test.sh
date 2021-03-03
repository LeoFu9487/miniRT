FILES=./tests/*/*.rt

for f in $FILES
do
	./miniRT $f --save
done
