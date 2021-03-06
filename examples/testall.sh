testdirs="boundaries cavity channel cylinder estuary iwaves lockexchange tides tides-restart wetdry windstress"

for dir in `echo $testdirs`
do
  echo Testing $dir
  make -C ../main clean >& /dev/null
  make -C $dir clobber >& /dev/null
  make -C $dir test >& $dir.out 

  failed=0
  if [ `grep -c blowing $dir.out` -ne 0 -o `grep -c Error $dir.out` -ne 0 -o `grep -c 'Timing Summary' $dir.out` -lt 1 ] ; then
      failed=1;
  fi
  
  if [ $failed -eq 1 ] ; then
      echo Error in running $dir test.
      echo Check $dir.out for details.
  else
      echo "Success!"
      rm -f $dir.out
      make -C $dir clobber >& /dev/null
  fi
done
