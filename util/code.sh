#!/bin/bash
for i in numerical graph/mst; do
  for src in "$i"/*.cpp; do
    base=$(echo "$src" | cut -d. -f1)
    dst=$base.lg
    sum=$base.sum
    case "$1" in
      gen)
	get "$src"
	util/stripcode header < "$src" |
	util/lgrind/source/lgrind -i - > "$dst"
	util/stripcode header preproc comments < "$src" |
	util/adler > "$sum"
	;;
      clean)
	echo "rm -f $dst $sum"
	rm -f "$dst" "$sum"
    esac
  done
done
