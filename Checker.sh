g++ -std=c++20 main.cpp -o original
g++ -std=c++20 stupid.cpp -o stupid
g++ -std=c++20 gen.cpp -o gen
declare -i var
while true;
do
    ./gen > input.txt
    ./stupid < input.txt > stupid_output.txt
    ./original < input.txt > original_output.txt
    var=var+1
    if diff original_output.txt stupid_output.txt > difference.txt;
    then
      echo "TEST:" $var "OK"
    else
        echo "WA"
        echo "TEST:"
        cat input.txt
        echo "\n"
        echo "Founded:"
        cat original_output.txt
        echo "\n"
        echo "Expected:"
        cat stupid_output.txt
        exit 0
    fi
done
