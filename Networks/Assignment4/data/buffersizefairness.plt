set terminal png
set output "buffersizefairness.png"
set title "Buffer Size vs Fairness plot"
set xlabel "Buffer Size(packets)"
set ylabel "Fairness"

set xrange [0:800]
plot "-"  title "Fairness" with linespoints
10 0.495655
20 0.546052
30 0.581439
40 0.602524
50 0.611633
60 0.611504
70 0.606407
80 0.606301
90 0.606197
100 0.606091
200 0.60497
300 0.603789
400 0.60255
500 0.601255
600 0.599909
700 0.598512
800 0.597072
e
