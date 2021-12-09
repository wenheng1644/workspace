#!/bin/bash
#实例：读取csv文件并输出到sql文件中

outfile="members.sql"
IFS=','

count=0
while read lname fname address city state zip;do

  count=$[ $count + 1 ]
  echo "show lame: $lame and count: $count"
  cat >> $outfile << EOF
    INSERT INTO members (lname,fname,address,city,state,zip) VALUES
  ('$lame','$fname','$address','$city','$state','$zip');
EOF
done < ${1}