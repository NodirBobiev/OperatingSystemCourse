 1773  ls -i
 1774  cd ..
 1775  find . -inum 16044073672513938 > ex2.txt
 1776  ls
 1777  nano ex2.txt
 1778  find . -inum 16044073672513938 -exec rm {}
 1779  find . -inum 16044073672513938 -exec rm {}
 1780  find . -inum 16044073672513938 -exec rm {};
 1781  find . -inum 16044073672513938 -exec rm {}\;
 1782  find . -inum 16044073672513938 -exec rm {} \;
 1783  ls
 1784  ls -i 16044073672513938 >> ex2.txt
 1785  ls -inum 16044073672513938 >> ex2.txt
 1786  ls
 1787  cd week01
 1788  ls
 1789  cd ..
 1790  nano ex2.txt
 1791  ls -i
 1792  nano ex1.sh
 1793  echo 'nothing is more important' > _ex2.txt
 1794  ls
 1795  link _ex2.txt week01/file.txt/
 1796  link _ex2.txt week01/file.txt
 1797  cd week01
 1798  ls
 1799  ls -i
 1800  cd ..
 1801  ls -i
 1802  find . -inum 4222124650688050 -exec rm {} \; >> ex2.txt
 1803  ls
 1804  nano ex2.txt
 1805  echo 'nothing is more important' > _ex2.txt
 1806  link _ex2.txt week01/file.txt
 1807  find . -inum 4222124650688050 -exec rm {} >> ex2.txt \;
 1808  ls
 1809  nano ex2.txt
 1810  nano _ex2.txt
 1811  ls -i
 1812  ls
 1813  nano ex2.txt
 1814  ls
 1815  find . -inum 4222124650688050 -exec rm {} \ >> ex2.txt;
 1816  nano ex2.txt
 1817  history 30 > ex2.sh
 1818  ls
 1819  nano ex2.sh
 1820  history 40 > ex2.sh
 1821  nano ex2.sh
 1822  history 50 > ex2.sh
