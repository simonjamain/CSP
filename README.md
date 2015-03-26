# CSP
#
# https://fedetft.wordpress.com/2010/03/07/cmake-part-3-finding-libraries/
#
# Installer or-tools dans un répertoire du path
git clone https://github.com/google/or-tools.git or-tools;
# Mac Users : Installer cmake dans le repertoire Application (http://www.cmake.org/download/ Binary osx distribution)
make third_party;
make cc;
# Known bugs
The linker of produced executables on osx can point to the wrong location : use otool to change it to the good or tool location
see (http://www.cmake.org/Wiki/CMake_RPATH_handling)