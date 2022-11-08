M=$(make)

echo $M
if [ "$M" = "make: 'csim' is up to date." ] || [ "$M" = "gcc -g -Wall -Werror -std=c99 -m64 -o csim csim.c" ]
then clear;
fi

printf "Forrit athugar hvort útkoma úr csim sé jöfn útkomu \ncsim-ref fyrir hverjca .trace skrá í traces möppunni\n"
printf "til að sjá gildi útkoma, notið flaggið '-v'\n\n"

IFS=" "
rStr='hitsmevconra:\n'

outStr=$([[ "$1" == "-v" ]] && echo "trace file|program|hits|misses|evictions|miss ratio\n" || echo "file|hits|misses|evictions|miss ratio\n")

for f in ./traces/*.trace; 
do
    mitt=$(./csim -s 4 -E 4 -b 6 -t $f | tr -d $rStr)
    hans=$(./csim-ref -s 4 -E 4 -b 6 -t $f | tr -d $rStr)

    read -a mArr <<< ${mitt} 
    read -a hArr <<< ${hans}
    
    if [ "$1" = "-v" ]
    then 
        outStr="$outStr${f:9:-6}|csim|${mArr[0]}|${mArr[1]}|${mArr[2]}|${mArr[3]}\n"
        outStr="$outStr${f:9:-6}|csim-ref|${hArr[0]}|${hArr[1]}|${hArr[2]}|${hArr[3]}\n"
    else
        hits=$([[ ${mArr[0]} == ${hArr[0]} ]] && echo "True" || echo "False")
        misses=$([[ ${mArr[1]} == ${hArr[1]} ]] && echo "True" || echo "False")
        evicts=$([[ ${mArr[2]} == ${hArr[2]} ]] && echo "True" || echo "False")
        ratios=$([[ ${mArr[3]} == ${hArr[3]} ]] && echo "True" || echo "False")
        outStr="$outStr${f:9:-6}|$hits|$misses|$evicts|$ratios\n"
    fi

done

echo -e $outStr > output.txt 
cat output.txt | column -t -s "|"