set terminal png
set output "svf.png"
plot "svf.txt" u 1:2 w boxes
