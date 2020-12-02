#!/bin/bash

./affichage tests/$1   sortie.dot
dot -Tpng -o arbre.png sortie.dot
