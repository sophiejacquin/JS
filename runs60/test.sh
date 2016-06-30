#!/bin/bash

i=1
s=1
while [ $i -le 20 ]; do 
var=test${i}
../JobShopEA  --inputFile="/home/jacquin/Documents/JSMulti/DataOneMachine/bky60/bky60_60.txt" --pCross=0.8447  --pMutCombined=0.9443 --pMut1=0.1512 --pMut=0.559 --popSize=13 --nb_lambda=3 -t60 --seed=$s>>"TestI1" 
let $[ s+=100 ]
let $[ i+=1 ] # incremente i de 1 a chaque boucle 
done

i=1
s=1
while [ $i -le 20 ]; do 
var=test${i}
../JobShopEA  --inputFile="/home/jacquin/Documents/JSMulti/DataOneMachine/bky60/bky60_120.txt" --pCross=0.8447  --pMutCombined=0.9443 --pMut1=0.1512 --pMut=0.559 --popSize=13 --nb_lambda=3  -t60 --seed=$s>>"TestI2" 
let $[ s+=100 ]
let $[ i+=1 ] # incremente i de 1 a chaque boucle 
done

i=1
s=1
while [ $i -le 20 ]; do 
var=test${i}
../JobShopEA  --inputFile="/home/jacquin/Documents/JSMulti/DataOneMachine/bky60/bky60_180.txt" --pCross=0.8447  --pMutCombined=0.9443 --pMut1=0.1512 --pMut=0.559 --popSize=13 --nb_lambda=3  -t60 --seed=$s>>"TestI3" 
let $[ s+=100 ]
let $[ i+=1 ] # incremente i de 1 a chaque boucle 
done

i=1
s=1
while [ $i -le 20 ]; do 
var=test${i}
../JobShopEA  --inputFile="/home/jacquin/Documents/JSMulti/DataOneMachine/bky60/bky60_240.txt" --pCross=0.8447  --pMutCombined=0.9443 --pMut1=0.1512 --pMut=0.559 --popSize=13 --nb_lambda=3  -t60 --seed=$s>>"TestI4" 
let $[ s+=100 ]
let $[ i+=1 ] # incremente i de 1 a chaque boucle 
done

i=1
s=1
while [ $i -le 20 ]; do 
var=test${i}
.../JobShopEA  --inputFile="/home/jacquin/Documents/JSMulti/DataOneMachine/bky60/bky60_300.txt" --pCross=0.8447  --pMutCombined=0.9443 --pMut1=0.1512 --pMut=0.559 --popSize=13 --nb_lambda=3  -t60--seed=$s>>"TestI5" 
let $[ s+=100 ]
let $[ i+=1 ] # incremente i de 1 a chaque boucle 
done
