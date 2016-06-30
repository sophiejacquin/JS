#!/bin/bash

i=1
s=1
while [ $i -le 20 ]; do 
var=test${i}
../JobShopEADICO  --inputFile="/home/jacquin/Documents/JSMulti/DataOneMachine/bky40/bky40_60.txt" --pCross=0.5625  --pMutCombined=0.8191 --pMut1=0.6073 --pMut=0.5992 --popSize=15 --nb_lambda=200 -t40 --seed=$s>>"TestI1" 
let $[ s+=100 ]
let $[ i+=1 ] # incremente i de 1 a chaque boucle 
done

i=1
s=1
while [ $i -le 20 ]; do 
var=test${i}
../JobShopEADICO  --inputFile="/home/jacquin/Documents/JSMulti/DataOneMachine/bky40/bky40_60.txt" --pCross=0.5625  --pMutCombined=0.8191 --pMut1=0.6073 --pMut=0.5992 --popSize=15 --nb_lambda=200 -t40 --seed=$s>>"TestI2" 
let $[ s+=100 ]
let $[ i+=1 ] # incremente i de 1 a chaque boucle 
done

i=1
s=1
while [ $i -le 20 ]; do 
var=test${i}
../JobShopEADICO  --inputFile="/home/jacquin/Documents/JSMulti/DataOneMachine/bky40/bky40_60.txt" --pCross=0.5625  --pMutCombined=0.8191 --pMut1=0.6073 --pMut=0.5992 --popSize=15 --nb_lambda=200 -t40 --seed=$s>>"TestI3" 
let $[ s+=100 ]
let $[ i+=1 ] # incremente i de 1 a chaque boucle 
done

i=1
s=1
while [ $i -le 20 ]; do 
var=test${i}
../JobShopEADICO  --inputFile="/home/jacquin/Documents/JSMulti/DataOneMachine/bky40/bky40_60.txt" --pCross=0.5625  --pMutCombined=0.8191 --pMut1=0.6073 --pMut=0.5992 --popSize=15 --nb_lambda=200 -t40 --seed=$s>>"TestI4" 
let $[ s+=100 ]
let $[ i+=1 ] # incremente i de 1 a chaque boucle 
done

i=1
s=1
while [ $i -le 20 ]; do 
var=test${i}
../JobShopEADICO  --inputFile="/home/jacquin/Documents/JSMulti/DataOneMachine/bky40/bky40_60.txt" --pCross=0.5625  --pMutCombined=0.8191 --pMut1=0.6073 --pMut=0.5992 --popSize=15 --nb_lambda=200 -t40 --seed=$s>>"TestI5" 
let $[ s+=100 ]
let $[ i+=1 ] # incremente i de 1 a chaque boucle 
done
