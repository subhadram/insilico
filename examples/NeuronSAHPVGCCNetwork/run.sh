if [ $1 = "m" ]; then
	if make -B SOURCE="main.cpp"; then
		./insilico.out -o out.dat -n nsets.isf -s ssets.isf
	fi
else
	./insilico.out -o out.dat -n nsets.isf -s ssets.isf
fi
