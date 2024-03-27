echo "Started executing at $(date)"
bash compute_it.sh 1 > out.1| bash compute_it.sh 2 > out.2
cat out.1
cat out.2
echo "Done executing at $(date)"
