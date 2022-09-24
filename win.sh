#!/bin/bash

SZ=(16 24 32 40 48 64 96 128 256)

for s in "${SZ[@]}"; do
	./omni_gen_icon_png $s;
done
