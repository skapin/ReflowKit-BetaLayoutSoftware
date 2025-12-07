lupdate *.cpp mainwindow.ui -ts *.ts
lrelease *.ts

rm -rf build/
mkdir -p build/
cd build/
qmake ..
make -j4
