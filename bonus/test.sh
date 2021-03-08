FILES=../tests/*/*.rt

for f in $FILES
do
	./miniRT_bonus $f --save
done
