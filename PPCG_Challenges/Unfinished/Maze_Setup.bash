#!/usr/bin/env bash
# Used when invoking `Maze.C` to reformat the input maze

# Old Version
Maze(){ gcc Maze.c;echo "$1"|sed -r "/^\s*$/{d};s/  (.)/ \1/g;s/--/-/g;s/I | I/II/;s/^ | $|[IU]$|^[IU]//g"|./a.out;}

# Current Version
WIP(){ M="$1";L=`echo "$M"|wc -l|sed "s/^\s*//"`;for((w=1;w<3;w++));do Q=$(echo "$M"|sed "$([ $w -eq 1 ]&&echo 2||echo $[L-1]){q};d");V=${#Q};for ((i=0;i<$V;i++));do if [ "${Q:$i:1}" = " " ];then K=$(echo "$M"|sed "$([ $w -eq 1 ]&&echo 1||echo $L){q};d"|sed "/^[^+|-]*$/{q};d");Q=${Q:0:$i}${K:$i:1}${Q:$i+1};fi;done;M=$([ -n "$K" ]&&echo "$(echo "$M"|sed "$([ $w -eq 1 ]&&echo 2||echo $[L-1]){c "$Q"
}")"||echo "$M");done;echo "$M";}
Maze(){ gcc Maze.c;P=$(WIP "$(echo "$1"|sed -r "s/  (.)/ \1/g;s/--/-/g")");echo "Reformatted Input Maze:";echo "$(echo "$P"|sed -r "/^[^|+-]*$/{d};s/I | I/II/;s/^ | $|[IU]$|^[IU]//g;s/U\+/ +/g")"|./a.out;}
Maze "$1"
