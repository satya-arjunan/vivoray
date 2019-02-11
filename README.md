
<img src="Vivoray.png" width="512">


Build on Ubuntu
---------------
sudo apt install qtcreator qtdeclarative5-dev qtmultimedia5-dev qtbase5-private-dev libqt5xmlpatterns5-dev libqt5svg5-dev libqt5webenginewidgets5 qtwebengine5-dev qtscript5-dev qttools5-dev libxt-dev libqt5x11extras5-dev
sudo apt install libcurl4-openssl-dev libssl-dev
sudo apt remove cmake
sudo pip install --upgrade cmake
export PATH=/usr/local/bin:$PATH
sudo apt install gfortran libqtwebkit-dev qt4-default
git clone git@github.com:/satya-arjunan/vivoray.git
cd vivoray
mkdir build
cd build
cmake -DQt5_DIR=/usr/lib/qt5 -DCMAKE_BUILD_TYPE:STRING=Debug -DSlicer_USE_SYSTEM_OpenSSL=1 -DSlicer_USE_SYSTEM_curl:BOOL=1 ../
make -j2
./Slicer-build/Vivoray
