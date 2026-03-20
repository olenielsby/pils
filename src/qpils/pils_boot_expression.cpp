/* This file is public domain */

#include "qpils-commander.h"

const char *PILS::PilsCommander::bootExpression =
	"[pils-configuration:executable-filename] <-#-* \"/\" repeat"
	"{ +$ fn"
	"| :ok"
	"  list := fn . \"pils/english/system/system.\" [pils-configuration:pils-filetype];"
	"  fn <-# 1 <-#-* \"/\""
	"}"
	".:list find"
	"{ filename"
	"| :where"
	"  ;text file (filename) text .:need; :ok"
	"  text -#=* \"><:[module:. pils system boot\""
	"  -#=* \"><;\" +#^* \"><:\" *=* [\"><.\", \"><\"]"
	"  .({} read:)"
	"  ---' (where)"
	"  boot: .filename .text"
	"}"
;
