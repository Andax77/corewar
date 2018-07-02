#!/bin/sh

NC='\033[0m' # No Color
RED='\033[0;31m'
YEL='\033[1;33m'
GRE='\033[0;32m'
BLU='\033[0;34m'

echo "${BLU}Running ${RED}Corewar Moulinette: ${NC}\n"

echo "${BLU}Making bin...${NC}"
cd .. && make
cd corewar_moulinette
USAGE=`./../corewar`
echo "${BLU}Done${NC}\n"

echo "${YEL}Testings :${NC}\n--------------------"

/bin/echo -n "NO ARGS ..."
if [ "`./../corewar`" == "$USAGE" ]
then echo "${GRE}\tOK${NC}\n"
else echo "${RED}\tKO${NC}\n"
fi

/bin/echo  "1 Zork ...\n"
echo `./../corewar zork.cor`
echo `./corewar zork.cor`
echo ""
if [ "`./../corewar zork.cor`" == "`./corewar zork.cor`" ]
then echo "${GRE}\tOK${NC}\n"
else echo "${RED}\tKO${NC}\n"
fi
