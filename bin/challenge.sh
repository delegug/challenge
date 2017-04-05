#!/bin/sh
appname=`basename $0 | sed s,\.sh$,,`

dirname=`dirname $0`
#tmp="${dirname#?}"

#if [ "${dirname%$tmp}" != "/" ]; then
#dirname=$PWD/$dirname
#fi
#LD_LIBRARY_PATH=$dirname
#export LD_LIBRARY_PATH
#export QML_IMPORT_PATH=`pwd`/qml
#export QML2_IMPORT_PATH=`pwd`/qml 
$dirname/$appname "$@"
