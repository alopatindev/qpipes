make clean
rm -vf *.o Makefile* {moc,qrc}_*.cpp qpipes qpipes.exe qpipes.pro
rm -rfv release debug *.Debug *.Release
cd images && ./clean.sh && cd ..
