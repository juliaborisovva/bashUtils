flagef=("hello" "-e [hk]ello" "-e hello -e kek -e тех," "-f test_data/flagfinput.txt")

unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    machine=Cygwin;;
    MINGW*)     machine=MinGw;;
    *)          machine="UNKNOWN:${unameOut}"
esac

if [ "$machine" == "Linux" ]
then
    flagsarr=(
    "" "-i" "-v" "-c" "-l" "-n" "-h" "-s" "-o"

    "-iv" "-ic" "-il" "-in" "-ih" "-is" "-io" "-vc" "-vl" "-vn"
    "-vh" "-vs" "-vo" "-cl" "-cn" "-ch" "-cs" "-co" "-ln" "-lh"
    "-ls" "-lo" "-nh" "-ns" "-no" "-hs" "-ho" "-so"

    "-ivc" "-ivl" "-ivn" "-ivh" "-ivs" "-ivo" "-icl" "-icn" "-ich" "-ics"
    "-ico" "-iln" "-ilh" "-ils" "-ilo" "-inh" "-ins" "-ino" "-ihs" "-iho"
    "-iso" "-vcl" "-vcn" "-vch" "-vcs" "-vco" "-vln" "-vlh" "-vls" "-vlo"
    "-vnh" "-vns" "-vno" "-vhs" "-vho" "-vso" "-cln" "-clh" "-cls" "-clo"
    "-cnh" "-cns" "-cno" "-chs" "-cho" "-cso" "-lnh" "-lns" "-lno" "-lhs"
    "-lho" "-lso" "-nhs" "-nho" "-nso" "-hso"

    "-ivcl" "-ivcn" "-ivch" "-ivcs" "-ivco" "-ivln" "-ivlh" "-ivls" "-ivlo" "-ivnh"
    "-ivns" "-ivno" "-ivhs" "-ivho" "-ivso" "-icln" "-iclh" "-icls" "-iclo" "-icnh"
    "-icns" "-icno" "-ichs" "-icho" "-icso" "-ilnh" "-ilns" "-ilno" "-ilhs" "-ilho"
    "-ilso" "-inhs" "-inho" "-inso" "-ihso" "-vcln" "-vclh" "-vcls" "-vclo" "-vcnh"
    "-vcns" "-vcno" "-vchs" "-vcho" "-vcso" "-vlnh" "-vlns" "-vlno" "-vlhs" "-vlho"
    "-vlso" "-vnhs" "-vnho" "-vnso" "-vhso" "-clnh" "-clns" "-clno" "-clhs" "-clho"
    "-clso" "-cnhs" "-cnho" "-cnso" "-chso" "-lnhs" "-lnho" "-lnso" "-lhso" "-nhso"

    "-ivcln" "-ivclh" "-ivcls" "-ivclo" "-ivcnh" "-ivcns" "-ivcno" "-ivchs" "-ivcho"
    "-ivcso" "-ivlnh" "-ivlns" "-ivlno" "-ivlhs" "-ivlho" "-ivlso" "-ivnhs" "-ivnho"
    "-ivnso" "-ivhso" "-iclnh" "-iclns" "-iclno" "-iclhs" "-iclho" "-iclso" "-icnhs"
    "-icnho" "-icnso" "-ichso" "-ilnhs" "-ilnho" "-ilnso" "-ilhso" "-inhso" "-vclnh"
    "-vclns" "-vclno" "-vclhs" "-vclho" "-vclso" "-vcnhs" "-vcnho" "-vcnso" "-vchso"
    "-vlnhs" "-vlnho" "-vlnso" "-vlhso" "-vnhso" "-clnhs" "-clnho" "-clnso" "-clhso"
    "-cnhso" "-lnhso"

    "-ivclnh" "-ivclns" "-ivclno" "-ivclhs" "-ivclho" "-ivclso" "-ivcnhs" "-ivcnho"
    "-ivcnso" "-ivchso" "-ivlnhs" "-ivlnho" "-ivlnso" "-ivlhso" "-ivnhso" "-iclnhs"
    "-iclnho" "-iclnso" "-iclhso" "-icnhso" "-ilnhso" "-vclnhs" "-vclnho" "-vclnso"
    "-vclhso" "-vcnhso" "-vlnhso" "-clnhso"

    "-ivclnhs" "-ivclnho" "-ivclnso" "-ivclhso" "-ivcnhso" "-ivlnhso" "-iclnhso" "-vclnhso"

    "-ivclnhso"
    )
else
    flagsarr=(
    "" "-i" "-v" "-c" "-l" "-n" "-h" "-s"

    "-iv" "-ic" "-il" "-in" "-ih" "-is" "-vc" "-vl" "-vn"
    "-vh" "-vs" "-vo" "-cn" "-ch" "-cs" "-co" "-ln" "-lh"
    "-ls" "-lo" "-nh" "-ns" "-hs"

    "-ivc" "-ivl" "-ivn" "-ivh" "-ivs" "-ivo" "-icn" "-ich" "-ics"
    "-ico" "-iln" "-ilh" "-ils" "-ilo" "-inh" "-ins" "-ihs"
    "-vcn" "-vch" "-vcs" "-vco" "-vln" "-vlh" "-vls" "-vlo"
    "-vnh" "-vns" "-vno" "-vhs" "-vho" "-vso" "-clo"
    "-cnh" "-cns" "-cno" "-chs" "-cho" "-cso" "-lnh" "-lns" "-lno" "-lhs"
    "-lho" "-lso" "-nhs"

    "-ivcn" "-ivch" "-ivcs" "-ivco" "-ivln" "-ivlh" "-ivls" "-ivlo" "-ivnh"
    "-ivns" "-ivno" "-ivhs" "-ivho" "-ivso" "-iclo" "-icnh"
    "-icns" "-icno" "-ichs" "-icho" "-icso" "-ilnh" "-ilns" "-ilno" "-ilhs" "-ilho"
    "-ilso" "-inhs" "-vclo" "-vcnh"
    "-vcns" "-vcno" "-vchs" "-vcho" "-vcso" "-vlnh" "-vlns" "-vlno" "-vlhs" "-vlho"
    "-vlso" "-vnhs" "-vnho" "-vnso" "-vhso" "-clno" "-clho"
    "-clso" "-cnhs" "-cnho" "-cnso" "-chso" "-lnhs" "-lnho" "-lnso" "-lhso"

    "-ivclo" "-ivcnh" "-ivcns" "-ivcno" "-ivchs" "-ivcho"
    "-ivcso" "-ivlnh" "-ivlns" "-ivlno" "-ivlhs" "-ivlho" "-ivlso" "-ivnhs" "-ivnho"
    "-ivnso" "-ivhso" "-iclno" "-iclho" "-iclso" "-icnhs"
    "-icnho" "-icnso" "-ichso" "-ilnhs" "-ilnho" "-ilnso" "-ilhso"
    "-vclno" "-vclho" "-vclso" "-vcnhs" "-vcnho" "-vcnso" "-vchso"
    "-vlnhs" "-vlnho" "-vlnso" "-vlhso" "-vnhso" "-clnho" "-clnso" "-clhso"
    "-cnhso" "-lnhso"

    "-ivclno" "-ivclho" "-ivclso" "-ivcnhs" "-ivcnho"
    "-ivcnso" "-ivchso" "-ivlnhs" "-ivlnho" "-ivlnso" "-ivlhso" "-ivnhso"
    "-iclnho" "-iclnso" "-iclhso" "-icnhso" "-ilnhso" "-vclnho" "-vclnso"
    "-vclhso" "-vcnhso" "-vlnhso" "-clnhso"

    "-ivclnho" "-ivclnso" "-ivclhso" "-ivcnhso" "-ivlnhso" "-iclnhso" "-vclnhso"

    "-ivclnhso"
    )
fi


files=("test_data/text2.txt test_data/text3.txt" "test_data/text.txt"
"test_data/text.file test_data/text2.file test_data/text3.file")

test_count=0
check=0
errors=0
res=""
tmp=""

for b in "${files[@]}"
do
    for a in "${flagef[@]}"
    do
        for t in "${flagsarr[@]}"
        do
            grep $a $t $b > orig.txt
            ./my_grep $a $t $b > my.txt
            echo "$(($test_count + 1)) testing... ./my_grep $a $t $b"

            # tmp=$(leaks --atExit -- ./my_grep $a $t $b | grep "")
            # tmp=$(valgrind --leak-check=full --leak-resolution=high --quiet ./my_grep $a $t $b | grep "^==")
            # valgrind --leak-check=full --leak-resolution=high ./my_grep

            if [ "$tmp" != "" ]
            then
              echo "'$t' Some blocks are definitely lost"
              res="lost"
            fi

            DIFF=$(diff -q orig.txt my.txt)
            if [ "$DIFF" != "" ]
            then
              echo "$(($test_count + 1)) testing... ./my_grep $a $t $b" >> errors.txt
              echo "'$t' $DIFF" >> errors.txt
              echo $a $t $b >> errors.txt
              echo orig >> errors.txt
              cat orig.txt >> errors.txt
              echo my >> errors.txt
              cat my.txt >> errors.txt
              echo >> errors.txt

              echo "$(($test_count + 1)) testing... ./my_grep $a $t $b"
              echo "'$t' $DIFF"
              echo $a $t $b
              echo orig
              cat orig.txt
              echo my
              cat my.txt
              echo
              check=1
              errors=$(($errors+1))
            fi
            test_count=$(($test_count+1))
            rm orig.txt my.txt
        done
    done
done

# if [ "$res" != "" ]
# then
#     echo "Some blocks are definitely lost"
# else
#     echo "All heap blocks were freed -- no leaks are possible"
# fi

if [[ $check -eq 0 ]]
then
    echo "All $test_count tests are correct"
else
    echo "Count of errors: "$errors "tests: "$test_count
fi
