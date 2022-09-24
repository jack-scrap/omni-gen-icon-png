#!/bin/bash

SZ=(16 32 128 256 512)

for s in "${SZ[@]}"; do
	./omni_gen_icon_png $s;
done
