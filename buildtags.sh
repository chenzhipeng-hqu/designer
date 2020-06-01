#! /bin/bash

#function fun_display_start_time()
#{
    #START_DATE=`date`
    #echo -en "\033[0;32;1m"
    #echo -e "********************************************"
    #echo -n "* Start build at "
    #echo $START_DATE
    #echo -en "********************************************"
    #echo -e "\033[0m"
#}

#function fun_display_finish_time()
#{
    #END_DATE=`date`
    #echo -en "\033[0;32;1m"
    #echo "********************************************"
    #echo -n "* Start build at "
    #echo $START_DATE
    #echo -n "* Stop  build at "
    #echo $END_DATE
    #echo -en "********************************************"
    #echo -e "\033[0m"
#}

#fun_display_start_time

echo "Now is building ctags"
start=$(date +%s)
ctags --tag-relative --sort=foldcase --fields=+l -Rf

echo "Now is building cscope tags"

find `pwd -P` -type f -iname "*.py" -o -type f -iname "*.c" -o -type f -iname "*.h" -o -type f -iname "*.cpp" -o -type f -iname "*.hpp" -o -type f -iname "*.java" -o -type f -iname "*.sh"  -o -type f -iname "*.inl" > cscope.files

#如果路径中含有空格，需要使用sed对生成的cscope.files文件进行处理，命令：
sed -i 's/^/"/;s/$/"/' cscope.files

cscope -RbqC -i cscope.files

rm -rf cscope.files

end=$(date +%s)
time=$(( $end - $start ))
echo Total time: ${time} sec

echo "finish"

if [ -f .ycm_extra_conf.py ]; then
    echo ".ycm_extra_conf.py exist."
else
    cp ~/.ycm_extra_conf.py .
fi


#fun_display_finish_time
