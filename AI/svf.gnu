set terminal png
set output "svf.png"
plot "svf.txt" u (log($1)):(log($2)) w boxes
