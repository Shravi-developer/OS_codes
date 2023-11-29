echo "Enter the value of n"
read n
a=0
b=1
count=2
echo "Fibonacci series:"
echo $a
echo $b
while [ $count -le $n ]
do
    let "fib = a + b"
    a=$b
    b=$fib
    echo $fib
    let "count = count + 1"
done
