mkdir lib;
cd lib;
	rm -rf kiwi/;

	git clone https://github.com/Nocte-/rhea.git rhea;

	cd rhea;
		mkdir build;
		cd build;
			cmake ..;
			make;
		cd ..
	cd ..;
cd ..;