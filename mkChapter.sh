#!/bin/bash

for i in 1 2 3 4 5 6 7 8 9 10; do
	mkdir "chapter"$i
	sudo chmod 777 "chapter"$i
	sudo chmod -w  "chapter"$i
done
