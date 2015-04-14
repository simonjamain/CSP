## instruction d'installation
### Mac OSX
* You then need to install the latest version of the [command line tools for XCode](https://developer.apple.com/downloads/index.action) (the full XCode isn't necessary).
* To install javac, just run javac. This will download and install Java.
* To install cmake, please use download the official .dmg archive from http://www.cmake.org/download.
### Ubuntu
For Ubuntu < 12.04:
```bash
$ sudo apt-get install bison flex python-setuptools python-dev autoconf \
  libtool zlib-devel texinfo gawk cmake
```
For Ubuntu >= 12.04:
```bash
$ sudo apt-get install bison flex python-setuptools python-dev autoconf \
  libtool texinfo gawk cmake
```
For Ubuntu >= 13.04:
```bash
$ sudo apt-get install bison flex python-setuptools python-dev autoconf \
  libtool zlib1g-dev texinfo gawk cmake
```
For Ubuntu >= 14.04:
```bash
$ sudo apt-get install bison flex python-setuptools python-dev autoconf \
  libtool zlib1g-dev texinfo gawk g++ curl texlive cmake
```
To use Java on Ubuntu, you need to install the jdk:
```bash
$ sudo apt-get install openjdk-7-jdk
```
To use .NET on ubuntu, you need to install mono. We recommend copying the mono archive (http://download.mono-project.com/sources/mono/mono-3.10.0.tar.bz2) to dependencies/archives instead of using the packaged mono-devel for Ubuntu, since 2.10.8 is old.

###Fedora
To install the dependencies:
```bash
$ sudo yum install subversion bison flex python-setuptools python-dev autoconf \
  libtool zlib-devel gawk cmake
```
###Debian
To install the dependencies:
```bash
$ sudo apt-get install bison flex python-setuptools python-dev autoconf libtool \
```
###Windows
Follow the windows section from this guide : [or-tools install guide](https://developers.google.com/optimization/installing#source_windows)

## Débuggage
Pour activer le déébuggage, passez la commande suivante a cmake :
```cmake
-DCMAKE_BUILD_TYPE=Debug
```
De plus, vous pouvez afficher sur la sortie standard les valeurs retournés par le solver en spécifiant cette option :
```cmake
-DCSP_LOG_VALUES=ON
```

## Known bugs
The linker of produced executables on osx can point to the wrong location : use otool to change it to the good or tool location
run : install_name_tool -change "/Users/lperron/Work/or-tools/lib/libortools.dylib" "/Users/doctorant/Desktop/lib/or-tools.MacOsX64/lib/libortools.dylib" runTests
see : (http://www.cmake.org/Wiki/CMake_RPATH_handling)

