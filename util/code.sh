#!/bin/bash
for i in numerical graph/mst; do
  for src in "$i"/*.cpp; do
    dst=$(echo "$src" | cut -d. -f1).lg
    case "$1" in
      gen)
	get "$src"
	util/stripcode header < "$src" |
	util/lgrind/source/lgrind -i - > "$dst"
	;;
      clean)
	echo "rm -f $dst"
	rm -f "$dst"
    esac
  done
done
