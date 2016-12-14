#!/bin/bash

set -e
set -x

echo "Bash version ${BASH_VERSION}..."

for dd in `seq 0.1 0.05 0.5`
do
    # Build TermTable
    tools/BitFunnel/src/BitFunnel termtable /tmp/wikipedia.100.200/config/ $dd PrivateSharedRank0And3
    # Run BitFunnel for output
    tools/BitFunnel/src/BitFunnel repl ~/dev/wikipedia.100.200/config/ -script ~/dev/wikipedia.100.200/script.output
    # Check output against verifier
    python3 ../src/Scripts/verify.py ~/dev/wikipedia.100.200/d20.groundTruth.csv ~/dev/BitFunnel/build-ninja/verificationOutput.csv /tmp/verified.csv    
    python3 ..//src/Scripts/sum-csv-column.py /tmp/verified.csv 3

    # Run BitFunnel for QPS
    tools/BitFunnel/src/BitFunnel repl ~/dev/wikipedia.100.200/config/ -script ~/dev/wikipedia.100.200/script.query
    # 6th line, 2nd field should be QPS.
    awk 'FNR == 6 {print $2}' /tmp/QuerySummaryStatistics.txt
done    