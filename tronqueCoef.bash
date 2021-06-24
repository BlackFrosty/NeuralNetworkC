#!/bin/bash
FIC_IN=CoeffOut.orig
FIC_OUT=CoeffOut.txt

tronque=$1

rm ${FIC_OUT}
cat ${FIC_IN}|while read ligne
do
	echo ${ligne}|cut -c1-$((${#ligne} - ${tronque})) >> ${FIC_OUT}
done
