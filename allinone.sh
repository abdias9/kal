echo "--- COMPILING... ---"
rm bin/kal.bin
rm kal.iso
cd src
make clean
make
cd ../
echo "--- BUILDING ISO... ---"
./buildiso.sh
echo "--- DEBUG STARTED. ---"
./debug.sh
echo "--- DEBUG FINISHED. ---"
