   28  git status
   29  history
   30  sudo losetup -f lofs.img
   31  sudo mkfs.ext4 $(losetup -a | grep 'lofs.img' | awk '{print $1}' | cut -d ':' -f 1)
   32  sudo mount $(losetup -a | grep 'lofs.img' | awk '{print $1}' | cut -d ':' -f 1) ./lofsdisk
   33  mkdir lofsdisk
   34  sudo mount $(losetup -a | grep 'lofs.img' | awk '{print $1}' | cut -d ':' -f 1) ./lofsdisk
   35  ls
   36  cd lofsdisk
   37  ls
   38  cd ..
   39  chmod 777 lofsdids/
   40  chmod 777 lofsdisk/
   41  echo 1 > lofsdisk/file1
   42  chmod 777 lofsdisk/
   43  sudo chmod 777 lofsdisk
   44  sudo chmod 777 lofsdisk/
   45  ls
   46  cd losfdisk
   47  ls
   48  cd lofsdisk
   49  ls
   50  cd ..
   51  echo 1 > lofsdisk/file1
   52  ls
   53  cd lofsdisk
   54  ls
   55  cd ..
   56  echo 2 > lofsdisk > file1
   57  echo 2 > lofsdisk/file1
   58  ls
   59  ls -l lofsdisk/
   60  echo 3 > lofsdisk/file1
   61  ls -l lofsdisk/
   62  df -H
   63  history
   64  history 35 > ex1.sh
   65  ls
   66  nano ex1.sh
   67  history 40 > ex1.sh
