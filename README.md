# ifes-po-2019-1

OR-Tools

https://scip.zib.de/download.php?fname=scipoptsuite-7.0.1.tgz
tar -xvzf scipoptsuite-7.0.1.tgz
cd scipoptsuite-7.0.1

make GMP=false READLINE=false TPI=none ZIMPL=false PARASCIP=true LPS=none USRCFLAGS=-fPIC USRCXXFLAGS=-fPIC USRCPPFLAGS=-fPIC scipoptlib install INSTALLDIR=/home/avelino/ifes-po-2019-1/scip

make GMP=false READLINE=false TPI=none ZIMPL=false PARASCIP=true LPS=none scipoptlib install INSTALLDIR=/home/avelino/ifes-po-2019-1/scip

git clone -b master https://github.com/google/or-tools
cd or-tools
make third_party

https://developers.google.com/optimization/install/cpp/source_linux#ubuntu-18.04
sudo apt-get -y install git wget pkg-config build-essential cmake autoconf libtool zlib1g-dev lsb-release

echo "UNIX_SCIP_DIR = /home/avelino/ifes-po-2019-1/scip" >> Makefile.local
make cc
make install_cc prefix=/home/avelino/ifes-po-2019-1/ortools

https://developers.google.com/optimization/install/cpp/source_mac
brew install swig

echo "UNIX_SCIP_DIR = /Users/avelino/Sources/ifes-po-2019-1/scip" >> Makefile.local
make cc
make install_cc prefix=/Users/avelino/Sources/ifes-po-2019-1/ortools

