i=1
while [ $i -lt 20 ] 
do
	echo $i
	cat test$i >> fronts
	let $[ i+=1 ] 
done
cat fronts | cut -d' ' -f -2 >>fronts2
