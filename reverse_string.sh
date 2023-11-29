read -p "Enter a string: " input_string
reversed_string=""

length=${#input_string}

for (( i=$length-1; i>=0; i-- )); 
do
    rev_string="${rev_string}${input_string:$i:1}"
done

echo "Reversed string: $rev_string"
