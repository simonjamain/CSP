#installing dependencies
mkdir lib;
cd lib;

#installing google test --------------------------------------------------------------------
rm -rf googletest/;

git clone http://git.chromium.org/external/googletest.git googletest;

#installing or-tools form binaries ---------------------------------------------------------
rm -rf or-tools/;

if [[ "$OSTYPE" == "linux-gnu" ]]; then
        # ...
	wget http://simon.jamain.emi.u-bordeaux.fr/ressources/or-tools/Google.OrTools.cc.Linux64.3853.tar.gz;
elif [[ "$OSTYPE" == "darwin"* ]]; then
	# Mac OSX
	# retrieve and unpack
	curl -o "or-tools.tar.gz" "http://simon.jamain.emi.u-bordeaux.fr/ressources/or-tools/Google.OrTools.cc.MacOsX64.3853.tar.gz";
	tar -xzf or-tools.tar.gz;
	rm or-tools.tar.gz;
	# rename
	mv or-tools.MacOsX64/ or-tools/;
	# install lib
	cd or-tools/;
	./install_libortools_mac.sh;
	cd ..;
#elif [[ "$OSTYPE" == "cygwin" ]]; then
        # POSIX compatibility layer and Linux environment emulation for Windows
#elif [[ "$OSTYPE" == "msys" ]]; then
        # Lightweight shell and GNU utilities compiled for Windows (part of MinGW)
#elif [[ "$OSTYPE" == "win32" ]]; then
        # I'm not sure this can happen.
#elif [[ "$OSTYPE" == "freebsd"* ]]; then
        # ...
fi

cd ..;