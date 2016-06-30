#!/bin/bash

i=1
s=1
while [ $i -le 20 ]; do 
var=test${i}
../JobShopEADICO  --inputFile="/home/jacquin/Documents/JSMulti/DataOneMachine/bky20/bky20_60.txt" --pCross=0.8731  --pMutCombined=0.3166 --pMut1=0.1461 --pMut=0.8715 --popSize=12 --nb_lambda=500 -t20 --seed=$s>>"TestI1" 
let $[ s+=100 ]
let $[ i+=1 ] # incremente i de 1 a chaque boucle 
done

i=1
s=1
while [ $i -le 20 ]; do 
var=test${i}
../JobShopEADICO  --inputFile="/home/jacquin/Documents/JSMulti/DataOneMachine/bky20/bky20_60.txt" --pCross=0.8731  --pMutCombined=0.3166 --pMut1=0.1461 --pMut=0.8715 --popSize=12 --nb_lambda=500 -t20 --seed=$s>>"TestI2" 
let $[ s+=100 ]
let $[ i+=1 ] # incremente i de 1 a chaque boucle 
done

i=1
s=1
while [ $i -le 20 ]; do 
var=test${i}
../JobShopEADICO  --inputFile="/home/jacquin/Documents/JSMulti/DataOneMachine/bky20/bky20_60.txt" --pCross=0.8731  --pMutCombined=0.3166 --pMut1=0.1461 --pMut=0.8715 --popSize=12 --nb_lambda=500 -t20 --seed=$s>>"TestI3" 
let $[ s+=100 ]
let $[ i+=1 ] # incremente i de 1 a chaque boucle 
done

i=1
s=1
while [ $i -le 20 ]; do 
var=test${i}
../JobShopEADICO  --inputFile="/home/jacquin/Documents/JSMulti/DataOneMachine/bky20/bky20_60.txt" --pCross=0.8731  --pMutCombined=0.3166 --pMut1=0.1461 --pMut=0.8715 --popSize=12 --nb_lambda=500 -t20 --seed=$s>>"TestI4" 
let $[ s+=100 ]
let $[ i+=1 ] # incremente i de 1 a chaque boucle 
done

i=1
s=1
while [ $i -le 20 ]; do 
var=test${i}
../JobShopEADICO  --inputFile="/home/jacquin/Documents/JSMulti/DataOneMachine/bky20/bky20_60.txt" --pCross=0.8731  --pMutCombined=0.3166 --pMut1=0.1461 --pMut=0.8715 --popSize=12 --nb_lambda=500 -t20 --seed=$s>>"TestI5" 
let $[ s+=100 ]
let $[ i+=1 ] # incremente i de 1 a chaque boucle 
done
