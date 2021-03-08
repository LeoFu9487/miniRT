FILES=./tests/*/*.rt

for f in $FILES
do
	echo $f
	./miniRT $f --save
done
