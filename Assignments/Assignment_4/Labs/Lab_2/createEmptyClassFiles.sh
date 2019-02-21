#!/bin/sh

echo "#ifndef MyClass_hh" > $1.hh
echo "#define MyClass_hh" >> $1.hh
echo >> $1.hh
echo "class MyClass" >> $1.hh
echo "{" >> $1.hh
echo "public:" >> $1.hh
echo "    MyClass();" >> $1.hh
echo "    ~MyClass();" >> $1.hh
echo >> $1.hh
echo "private:" >> $1.hh
echo "};" >> $1.hh
echo "#endif" >> $1.hh

echo "#include \"./MyClass.hh"\" >> $1.cc
echo "MyClass::MyClass()" >> $1.cc
echo "{" >> $1.cc
echo "}" >> $1.cc
echo "MyClass::~MyClass()" >> $1.cc
echo "{" >> $1.cc
echo "}" >> $1.cc


