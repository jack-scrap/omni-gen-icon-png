#!/bin/bash

SZ=(16 32 64 128)

for s in "${SZ[@]}"; do
	./omni_gen_icon $s;
done
