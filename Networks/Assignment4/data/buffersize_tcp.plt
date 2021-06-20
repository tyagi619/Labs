set terminal png
set output "buffersize_tcp.png"
set title "Buffer Size vs Throughput(TCP)"
set xlabel "Buffer Size(packets)"
set ylabel "Throughput(in mbps)"

set xrange [0:800]
plot "-"  title "TCP flow" with linespoints
10 3.17899
20 6.21649
30 9.20844
40 12.1547
50 15.0737
60 17.9555
70 20.2922
80 20.3261
90 20.36
100 20.3941
200 20.7276
300 21.061
400 21.3944
500 21.7275
600 22.061
700 22.3942
800 22.7276
e
