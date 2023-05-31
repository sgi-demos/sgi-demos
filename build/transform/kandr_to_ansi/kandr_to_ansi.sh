# kandr_to_ansi.sh
#
# Convert from K&R style function declarations to ANSI C using cproto.
# Replaces input file's ".c" with "_to_ansi.c"
#
# Install:
#
# brew install cproto
#
# Usage:
# 
# ./kandr_to_ansi.sh kandr.c
#
fullfile="$1"                                   # filename with full path
filename=$(basename -- "$fullfile")             # filename without full path
extension="${filename##*.}"                     # file extension
dirname=$(dirname "$fullfile")                  # full path
basename=$(basename "$filename" ".$extension")  # base filename without extension
fullbasename="${dirname}/${basename}"
ansifile="$fullbasename"_to_ansi.c

# cproto options:
# -a  convert k&r to ansi
# -p  don't upgrade char and short params to int
# -q  don't complain about reading header files
# -o  NOT USED - should direct output to file, but doesn't work, so make copy instead
#
echo Converting $1 to $ansifile
cp $1 $ansifile
cproto -a -p -q $ansifile