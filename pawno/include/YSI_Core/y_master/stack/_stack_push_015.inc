/*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 the "License"; you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright C 2011
	the Initial Developer. All Rights Reserved.

Contributors:
	Y_Less
	koolk
	JoeBullet/Google63
	g_aSlice/Slice
	Misiur
	samphunter
	tianmeta
	maddinat0r
	spacemud
	Crayder
	Dayvison
	Ahmad45123
	Zeex
	irinel1996
	Yiin-
	Chaprnks
	Konstantinos
	Masterchen09
	Southclaws
	PatchwerkQWER
	m0k1
	paulommu
	udan111
	Cheaterman

Thanks:
	JoeBullet/Google63 - Handy arbitrary ASM jump code using SCTRL.
	ZeeX - Very productive conversations.
	koolk - IsPlayerinAreaEx code.
	TheAlpha - Danish translation.
	breadfish - German translation.
	Fireburn - Dutch translation.
	yom - French translation.
	50p - Polish translation.
	Zamaroht - Spanish translation.
	Los - Portuguese translation.
	Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes for
		me to strive to better.
	Pixels^ - Running XScripters where the idea was born.
	Matite - Pestering me to release it and using it.

Very special thanks to:
	Thiadmer - PAWN, whose limits continue to amaze me!
	Kye/Kalcor - SA:MP.
	SA:MP Team past, present and future - SA:MP.

Optional plugins:
	Gamer_Z - GPS.
	Incognito - Streamer.
	Me - sscanf2, fixes2, Whirlpool.
*/

#if defined _inc__stack_push_015
	#undef _inc__stack_push_015
#endif

#undef _YSIM_PUSH_INDEX
#define _YSIM_PUSH_INDEX 16
#if defined _YSIM_STACK_SLOT_15
	#undef _YSIM_STACK_SLOT_15
#endif
#if     _MASTER == 0
	#define _YSIM_STACK_SLOT_15 0
	#endinput
#elseif _MASTER == 1
	#define _YSIM_STACK_SLOT_15 1
	#endinput
#elseif _MASTER == 2
	#define _YSIM_STACK_SLOT_15 2
	#endinput
#elseif _MASTER == 3
	#define _YSIM_STACK_SLOT_15 3
	#endinput
#elseif _MASTER == 4
	#define _YSIM_STACK_SLOT_15 4
	#endinput
#elseif _MASTER == 5
	#define _YSIM_STACK_SLOT_15 5
	#endinput
#elseif _MASTER == 6
	#define _YSIM_STACK_SLOT_15 6
	#endinput
#elseif _MASTER == 7
	#define _YSIM_STACK_SLOT_15 7
	#endinput
#elseif _MASTER == 8
	#define _YSIM_STACK_SLOT_15 8
	#endinput
#elseif _MASTER == 9
	#define _YSIM_STACK_SLOT_15 9
	#endinput
#elseif _MASTER == 10
	#define _YSIM_STACK_SLOT_15 10
	#endinput
#elseif _MASTER == 11
	#define _YSIM_STACK_SLOT_15 11
	#endinput
#elseif _MASTER == 12
	#define _YSIM_STACK_SLOT_15 12
	#endinput
#elseif _MASTER == 13
	#define _YSIM_STACK_SLOT_15 13
	#endinput
#elseif _MASTER == 14
	#define _YSIM_STACK_SLOT_15 14
	#endinput
#elseif _MASTER == 15
	#define _YSIM_STACK_SLOT_15 15
	#endinput
#elseif _MASTER == 16
	#define _YSIM_STACK_SLOT_15 16
	#endinput
#elseif _MASTER == 17
	#define _YSIM_STACK_SLOT_15 17
	#endinput
#elseif _MASTER == 18
	#define _YSIM_STACK_SLOT_15 18
	#endinput
#elseif _MASTER == 19
	#define _YSIM_STACK_SLOT_15 19
	#endinput
#elseif _MASTER == 20
	#define _YSIM_STACK_SLOT_15 20
	#endinput
#elseif _MASTER == 21
	#define _YSIM_STACK_SLOT_15 21
	#endinput
#elseif _MASTER == 22
	#define _YSIM_STACK_SLOT_15 22
	#endinput
#elseif _MASTER == 23
	#define _YSIM_STACK_SLOT_15 23
	#endinput
#elseif _MASTER == 24
	#define _YSIM_STACK_SLOT_15 24
	#endinput
#elseif _MASTER == 25
	#define _YSIM_STACK_SLOT_15 25
	#endinput
#elseif _MASTER == 26
	#define _YSIM_STACK_SLOT_15 26
	#endinput
#elseif _MASTER == 27
	#define _YSIM_STACK_SLOT_15 27
	#endinput
#elseif _MASTER == 28
	#define _YSIM_STACK_SLOT_15 28
	#endinput
#elseif _MASTER == 29
	#define _YSIM_STACK_SLOT_15 29
	#endinput
#elseif _MASTER == 30
	#define _YSIM_STACK_SLOT_15 30
	#endinput
#elseif _MASTER == 31
	#define _YSIM_STACK_SLOT_15 31
	#endinput
#elseif _MASTER == 32
	#define _YSIM_STACK_SLOT_15 32
	#endinput
#elseif _MASTER == 33
	#define _YSIM_STACK_SLOT_15 33
	#endinput
#elseif _MASTER == 34
	#define _YSIM_STACK_SLOT_15 34
	#endinput
#elseif _MASTER == 35
	#define _YSIM_STACK_SLOT_15 35
	#endinput
#elseif _MASTER == 36
	#define _YSIM_STACK_SLOT_15 36
	#endinput
#elseif _MASTER == 37
	#define _YSIM_STACK_SLOT_15 37
	#endinput
#elseif _MASTER == 38
	#define _YSIM_STACK_SLOT_15 38
	#endinput
#elseif _MASTER == 39
	#define _YSIM_STACK_SLOT_15 39
	#endinput
#elseif _MASTER == 40
	#define _YSIM_STACK_SLOT_15 40
	#endinput
#elseif _MASTER == 41
	#define _YSIM_STACK_SLOT_15 41
	#endinput
#elseif _MASTER == 42
	#define _YSIM_STACK_SLOT_15 42
	#endinput
#elseif _MASTER == 43
	#define _YSIM_STACK_SLOT_15 43
	#endinput
#elseif _MASTER == 44
	#define _YSIM_STACK_SLOT_15 44
	#endinput
#elseif _MASTER == 45
	#define _YSIM_STACK_SLOT_15 45
	#endinput
#elseif _MASTER == 46
	#define _YSIM_STACK_SLOT_15 46
	#endinput
#elseif _MASTER == 47
	#define _YSIM_STACK_SLOT_15 47
	#endinput
#elseif _MASTER == 48
	#define _YSIM_STACK_SLOT_15 48
	#endinput
#elseif _MASTER == 49
	#define _YSIM_STACK_SLOT_15 49
	#endinput
#elseif _MASTER == 50
	#define _YSIM_STACK_SLOT_15 50
	#endinput
#elseif _MASTER == 51
	#define _YSIM_STACK_SLOT_15 51
	#endinput
#elseif _MASTER == 52
	#define _YSIM_STACK_SLOT_15 52
	#endinput
#elseif _MASTER == 53
	#define _YSIM_STACK_SLOT_15 53
	#endinput
#elseif _MASTER == 54
	#define _YSIM_STACK_SLOT_15 54
	#endinput
#elseif _MASTER == 55
	#define _YSIM_STACK_SLOT_15 55
	#endinput
#elseif _MASTER == 56
	#define _YSIM_STACK_SLOT_15 56
	#endinput
#elseif _MASTER == 57
	#define _YSIM_STACK_SLOT_15 57
	#endinput
#elseif _MASTER == 58
	#define _YSIM_STACK_SLOT_15 58
	#endinput
#elseif _MASTER == 59
	#define _YSIM_STACK_SLOT_15 59
	#endinput
#elseif _MASTER == 60
	#define _YSIM_STACK_SLOT_15 60
	#endinput
#elseif _MASTER == 61
	#define _YSIM_STACK_SLOT_15 61
	#endinput
#elseif _MASTER == 62
	#define _YSIM_STACK_SLOT_15 62
	#endinput
#elseif _MASTER == 63
	#define _YSIM_STACK_SLOT_15 63
	#endinput
#endif

