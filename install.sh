#installing dependencies
mkdir lib;
cd lib;

#installing google test
git clone http://git.chromium.org/external/googletest.git googletest;

#installing or-tools
git clone https://github.com/google/or-tools.git or-tools;
cd or-tools;
make third_party;
make install_python_modules;
make all;
make clean_third_party;

cd ..;
