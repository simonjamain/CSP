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
run : install_name_tool -change "/Users/lperron/Work/or-tools/lib/libortools.dylib" "/Users/doctorant/Desktop/lib/or-tools.MacOsX64/lib/libortools.dylib" runTests
see : (http://www.cmake.org/Wiki/CMake_RPATH_handling)
# Other
pour debugger :
-DCMAKE_BUILD_TYPE=Debug

dans csp.hpp 
#define CSP_DEBUG_DISPLAY_VALUE 1
provoque un affichage des valeurs de timenode trouvés
