#! /bin/bash

cd crab_0_120913_135758/res/
foreach file(*.xml)
        cat $file | sed -e "s/store/\/store/g" | sed -e "s/\/\/store/\/store/g"  > $file.tmp
        mv -f $file.tmp $file
end
cd ../../
