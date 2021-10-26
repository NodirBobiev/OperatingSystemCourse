touch _ex3.txt

echo 'nothing is more important' > _ex3.txt
ls -l _ex3.txt
chmod a-x _ex3.txt
ls -l _ex3.txt
chmod u+rwx, o+rwx _ex3.txt
ls -l _ex3.txt
chmod g=u _ex3.txt
ls -l _ex3.txt

rm _ex3.txt
