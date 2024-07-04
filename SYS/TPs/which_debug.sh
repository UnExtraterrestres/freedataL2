#!/bin/dash

if [ $# -ne 1 ]; then
  echo "Usage: $0 PROGRAMNAME" >&2
  exit 1
fi

IFS=':'

# Début du débuggage
# activation avec set des options -x  et -v
#   -v verbose       The shell writes its input (commands) to standard error as it is read.  Useful for debugging.
#   -x xtrace        Write each command to standard error (preceded by a ‘+ ’) before it is executed.  Useful for debugging.
set -xv

for ONE_DIR in $PATH; do
  if test -f "$ONE_DIR/$1" && test -x "$ONE_DIR/$1"; then
    echo "$ONE_DIR/$1"
    exit 0
  fi
done

# Fin du débuggage
# Désactivation des options -x et -v
set +xv

echo "no $1 in ($PATH)" >&2
exit 1
