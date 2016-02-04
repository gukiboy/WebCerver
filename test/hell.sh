#!/bin/sh
export IP="54.164.99.81"

if [ -z $1 ]
then
echo "test 1"
    {
        for ((i=0; i<10000; i++))
        do
            echo "oi $i"
            #sleep 0.0001;
            #sleep 1
        done
    } | telnet $IP 3490
fi

if [ 1 -eq $1 ]
then
echo "test 2"
    {
        for ((i=0; i<10000; i++))
        do
            echo "oi $i"
            sleep 1
        done
    } | telnet $IP 3490

fi

if [ 2 -eq $1 ]
then
echo "test 3"

    {
        for ((i=0; i<2; i++))
        do
                echo "$(cat text)"
        done
    } | telnet $IP 3490

fi

if [ 3 -eq $1 ]
then
echo "test 4"

    for ((i=0; i<2; i++))
    do
      echo "$(cat text)"
    done
fi

