#!/bin/bash
--pCross 0.4089 --pMut  --pMut1  --pMut2  --nbLambda 2 --popSize 11
i=1
s=1
while [ $i -le 20 ]; do 
var=test${i}
../JobShopEA  --inputFile="/home/jacquin/Documents/JSMulti/DataOneMachine/bky100/bky100_60.txt" --pCross=0.4089  --pMutCombined=0.8891 --pMut1=0.0647 --pMut=0.902 --popSize=11 --nb_lambda=2 -t80 --seed=$s>>"TestI1" 
let $[ s+=100 ]
let $[ i+=1 ] # incremente i de 1 a chaque boucle 
done

i=1
s=1
while [ $i -le 20 ]; do 
var=test${i}
../JobShopEA  --inputFile="/home/jacquin/Documents/JSMulti/DataOneMachine/bky100/bky100_120.txt" -pCross=0.4089  --pMutCombined=0.8891 --pMut1=0.0647 --pMut=0.902 --popSize=11 --nb_lambda=2 -t80 --seed=$s>>"TestI2" 
let $[ s+=100 ]
let $[ i+=1 ] # incremente i de 1 a chaque boucle 
done

i=1
s=1
while [ $i -le 20 ]; do 
var=test${i}
../JobShopEA  --inputFile="/home/jacquin/Documents/JSMulti/DataOneMachine/bky100/bky100_180.txt" -pCross=0.4089  --pMutCombined=0.8891 --pMut1=0.0647 --pMut=0.902 --popSize=11 --nb_lambda=2 -t80 --seed=$s>>"TestI3" 
let $[ s+=100 ]
let $[ i+=1 ] # incremente i de 1 a chaque boucle 
done

i=1
s=1
while [ $i -le 20 ]; do 
var=test${i}
../JobShopEA  --inputFile="/home/jacquin/Documents/JSMulti/DataOneMachine/bky100/bky100_240.txt" -pCross=0.4089  --pMutCombined=0.8891 --pMut1=0.0647 --pMut=0.902 --popSize=11 --nb_lambda=2 -t80 --seed=$s>>"TestI4" 
let $[ s+=100 ]
let $[ i+=1 ] # incremente i de 1 a chaque boucle 
done

i=1
s=1
while [ $i -le 20 ]; do 
var=test${i}
../JobShopEA  --inputFile="/home/jacquin/Documents/JSMulti/DataOneMachine/bky100/bky100_300.txt" -pCross=0.4089  --pMutCombined=0.8891 --pMut1=0.0647 --pMut=0.902 --popSize=11 --nb_lambda=2 -t80 --seed=$s>>"TestI5" 
let $[ s+=100 ]
let $[ i+=1 ] # incremente i de 1 a chaque boucle 
done
