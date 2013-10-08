#
# Torbert, 4 October 2013
#
# srand( 12345 )
#
# grid size 100 x 100
#
# transition... linked list
#
# prob = 0.0 : 0.1 : 1.0
#
# total runtime 43 seconds
#
set terminal png
set output "simq.png"
set xrange[0:1]
set title "Average Time over 10,000 Trials"
set xlabel "probability"
set ylabel "burnout time"
plot "simq.txt" with lines notitle,\
     "simq.txt" with points pt 5 notitle
#
# end of file
#
