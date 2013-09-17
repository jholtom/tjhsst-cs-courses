set terminal png
set output "dvf.png"
plot "dvf.txt" u 1:2 w l notitle
