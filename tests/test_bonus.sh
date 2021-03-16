FILES=./*/*.rt

for f in $FILES
do
	echo $f
	../miniRT_bonus $f --save
done
