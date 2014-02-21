#!/bin/bash

# Plots data with gnuplot
gnuplot - <<PLOT
set terminal pngcairo
set output '$2'
set border 3
set xtics nomirror rotate by 270 font "Droid Sans, 10"
set ytics nomirror font "Droid Sans, 10"
unset key
plot '$1' using 1:2 with points pointtype 7 pointsize 1 lt rgb 'black'
pause mouse
PLOT
