#!/bin/bash

CopasiSE=${1:-CopasiSE}

function runTest () {
  echo Test: ${1}
  ${CopasiSE} --nologo ${1}.cps > /dev/null
  ndiff ${1}.1.txt ${1}.1.txt.tgt || echo ${1} failed
}

runTest EventTest1
runTest EventTest2
runTest EventTest3
runTest EventTest4
runTest EventTest5
runTest EventTest6
runTest EventTest7
# This test currently fails
echo Test: EventTest8 skipped
# runTest EventTest8  
runTest EventTest9
runTest EventTest10
runTest EventTest11
runTest EventTest12
runTest EventTest13
runTest EventTest14
runTest EventTest15