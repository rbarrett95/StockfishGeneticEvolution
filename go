#! /bin/bash -f
# csh not currently available on CS linux cluster
# --> modified to be a bash script, CBC, Thu Oct 17 10:29:34 2013
# modified by CBC to require both arguments and to show usage
if [ -z "$2" ]
then
  echo "usage: go [function] [file ext], e.g., go f1 ex1"
  echo "  this will use files f1.c, in.ex1, and template.ex1"
  exit 1
else
  echo "    Note: Genesis files modified for use on Linux cluster"
  echo "    Note2: ga.$1 is your executable"
  echo "           (e.g., if you need to use the debugger)"
  echo "    making executables ..."
  make f=$1 ga.$1
  make report
  echo "    running ga.$1 $2 ..."
  ga.$1 $2
  echo "    writing report ..."
  echo rep.$2 for ga.$1 > rep.$2
  date >> rep.$2
  echo ' ' >> rep.$2
  report $2 >> rep.$2
  echo "    done."
fi
