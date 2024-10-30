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
    flagsArr=("-b" "-e" "-n" "-s" "-t" "-v" "-E" "-T"

    "-be" "-bn" "-bs" "-bt" "-bv" "-bE" "-bT" "-en" "-es" "-et"
    "-ev" "-eE" "-eT" "-ns" "-nt" "-nv" "-nE" "-nT" "-st" "-sv"
    "-sE" "-sT" "-tv" "-tE" "-tT" "-vE" "-vT" "-ET"

    "-ben" "-bes" "-bet" "-bev" "-beE" "-beT" "-bns" "-bnt" "-bnv"
    "-bnE" "-bnT" "-bst" "-bsv" "-bsE" "-bsT" "-btv" "-btE" "-btT"
    "-bvE" "-bvT" "-bET" "-ens" "-ent" "-env" "-enE" "-enT" "-est"
    "-esv" "-esE" "-esT" "-etv" "-etE" "-etT" "-evE" "-evT" "-eET"
    "-nst" "-nsv" "-nsE" "-nsT" "-ntv" "-ntE" "-ntT" "-nvE" "-nvT"
    "-nET" "-stv" "-stE" "-stT" "-svE" "-svT" "-sET" "-tvE" "-tvT"
    "-tET" "-vET"

    "-bens" "-bent" "-benv" "-benE" "-benT" "-best" "-besv" "-besE"
    "-besT" "-betv" "-betE" "-betT" "-bevE" "-bevT" "-beET" "-bnst"
    "-bnsv" "-bnsE" "-bnsT" "-bntv" "-bntE" "-bntT" "-bnvE" "-bnvT"
    "-bnET" "-bstv" "-bstE" "-bstT" "-bsvE" "-bsvT" "-bsET" "-btvE"
    "-btvT" "-btET" "-bvET" "-enst" "-ensv" "-ensE" "-ensT" "-entv"
    "-entE" "-entT" "-envE" "-envT" "-enET" "-estv" "-estE" "-estT"
    "-esvE" "-esvT" "-esET" "-etvE" "-etvT" "-etET" "-evET" "-nstv"
    "-nstE" "-nstT" "-nsvE" "-nsvT" "-nsET" "-ntvE" "-ntvT" "-ntET"
    "-nvET" "-stvE" "-stvT" "-stET" "-svET" "-tvET"

    "-benst" "-bensv" "-bensE" "-bensT" "-bentv" "-bentE" "-bentT"
    "-benvE" "-benvT" "-benET" "-bestv" "-bestE" "-bestT" "-besvE"
    "-besvT" "-besET" "-betvE" "-betvT" "-betET" "-bevET" "-bnstv"
    "-bnstE" "-bnstT" "-bnsvE" "-bnsvT" "-bnsET" "-bntvE" "-bntvT"
    "-bntET" "-bnvET" "-bstvE" "-bstvT" "-bstET" "-bsvET" "-btvET"
    "-enstv" "-enstE" "-enstT" "-ensvE" "-ensvT" "-ensET" "-entvE"
    "-entvT" "-entET" "-envET" "-estvE" "-estvT" "-estET" "-esvET"
    "-etvET" "-nstvE" "-nstvT" "-nstET" "-nsvET" "-ntvET" "-stvET"

    "-benstv" "-benstE" "-benstT" "-bensvE" "-bensvT" "-bensET"
    "-bentvE" "-bentvT" "-bentET" "-benvET" "-bestvE" "-bestvT"
    "-bestET" "-besvET" "-betvET" "-bnstvE" "-bnstvT" "-bnstET"
    "-bnsvET" "-bntvET" "-bstvET" "-enstvE" "-enstvT" "-enstET"
    "-ensvET" "-entvET" "-estvET" "-nstvET"

    "-benstvE" "-benstvT" "-benstET" "-bensvET" "-bentvET"
    "-bestvET" "-bnstvET" "-enstvET"

    "-benstvET" "--number-nonblank" "--number" "--squeeze-blank"
    )
else
    flagsArr=("-b" "-e" "-n" "-s" "-t" "-v"

    "-be" "-bn" "-bs" "-bt" "-bv" "-en" "-es" "-et"
    "-ev" "-ns" "-nt" "-nv" "-st" "-sv" "-tv"

    "-ben" "-bes" "-bet" "-bev" "-bns" "-bnt" "-bnv"
    "-bst" "-bsv" "-btv" "-ens" "-ent" "-env" "-est"
    "-esv" "-etv" "-nst" "-nsv" "-ntv" "-stv"

    "-bens" "-bent" "-benv" "-best" "-besv" "-betv" "-bnst"
    "-bnsv" "-bntv" "-bstv" "-enst" "-ensv" "-entv" "-estv" "-nstv"

    "-benst" "-bensv" "-bentv"
    "-bestv" "-bnstv" "-enstv" "-benstv"
    )
fi

files=("test_data/text.txt test_data/text2.txt" "test_data/text.txt")

test_count=0
check=0
errors=0
res=""
tmp=""

for b in "${files[@]}"
do
    for t in "${flagsArr[@]}"
    do
      cat $t $b > orig.txt
      ./my_cat $t $b > my.txt
      echo "$(($test_count + 1)) testing... ./my_cat $t $b"

      # tmp=$(leaks --atExit -- ./my_cat $t $b)
      # tmp=$(valgrind --leak-check=full --leak-resolution=high --quiet ./my_cat $t $b | grep "blocks are definitely lost")

      if [ "$tmp" != "" ]
      then
          echo "'$t' Some blocks are definitely lost"
          res="lost"
      fi

      DIFF=$(diff -q orig.txt my.txt)
      if [ "$DIFF" != "" ]
      then
            echo "'$t' $DIFF"
            echo "$(($test_count + 1)) test... ./my_cat $t $b"
            check=1
            errors=$(($errors+1))
      fi
      test_count=$(($test_count+1))
      rm orig.txt my.txt
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
