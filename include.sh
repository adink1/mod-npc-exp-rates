#!/usr/bin/env bash
	
	MOD_NPC_EXP_RATES_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )/" && pwd )"
	
	source $MOD_NPC_EXP_RATES_ROOT"/conf/conf.sh.dist"
	
	if [ -f $MOD_NPC_EXP_RATES_ROOT"/conf/conf.sh" ]; then
	    source $MOD_NPC_EXP_RATES_ROOT"/conf/conf.sh"
	fi
