#!/bin/sh



#Start of the script
echo "Welcome to the Libre-OS Configuration Script"
echo -n "What arch do you want to build for: 1.)iX86 2.)x86_64 3.)ARM\n"
read answer
if echo "$answer" | grep -iq "1" ;then
  arch="ix86"
elif echo "$answer" | grep -iq "2" ;then
  arch="x86_64"
else
  arch="ARM"
fi

echo -n "Do you want MultiThreading Support? (y/n)?\n"
read answer
if echo "$answer" | grep -iq "^y" ;then
    mtEnabled="y"
else
    mtEnabled="n"
fi





#Configuring the header file
echo "#ifndef CONFIG_H_\n#define CONFIG_H_\n\n\n" > config.h.tmp
if echo "$arch" | grep -iq "ix86" ;then
  echo "#define __IX86__ 1 \n#undef __X86_64__ \n#undef __ARM__\n" >> config.h.tmp
elif echo "$arch" | grep -iq "x86_64" ;then
  echo "#undef __IX86__ \n#define __X86_64__ 1\n#undef __ARM__\n" >> config.h.tmp
else
  echo "#undef __IX86__ \n#undef __X86_64__ \n#define __ARM__ 1\n\n\n" >> config.h.tmp
fi


if echo "$mtEnabled" | grep -iq "^y" ;then
  mtStr = "MT_Enabled defined"
  echo "#define _MT_ENABLED 1\n" >> config.h.tmp

else
  mtStr = "MT_Enabled undefined"
  echo "#undef _MT_ENABLED\n" >>config.h.tmp
fi

#end the headerfile
echo "#endif //CONFIG_H_" >> config.h.tmp

mv config.h.tmp ../include/config.h

echo "${arch}"
echo "$mtStr"
