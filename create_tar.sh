set -x
rm -rf tmp
rm -f final2.tar.gz
mkdir tmp
cp *.h tmp/
cp *.cpp tmp/
cd tmp
rm -f test_runner.h
tar -czf ../final2.tar.gz *
cd ..
