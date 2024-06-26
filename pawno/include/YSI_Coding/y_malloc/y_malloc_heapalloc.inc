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

// Allocate some space right at the top of the stack for callback parameters.
#if !defined YSI_DEFAULT_MALLOC
	// Will actually allocate 271 bytes (rounds up to 16n-1).
	#define YSI_DEFAULT_MALLOC (256)
#endif

forward Alloc:Malloc_Allocate(size, const bool:clear = false);

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Finds all "BOUNDS 0" OpCodes in the AMX and rewrites them to "NOP NOP".  The
 *  byte pattern for this code is "OP_BOUNDS 0", which (AFAIK) can not appear
 *  anywhere else in the COD segment.  You can have "OP_BOUNDS" as a parameter
 *  to something, but it would then be followed by an OpCode of "0", which is
 *  never valid (OP_NONE).
 * </remarks>
 *//*------------------------------------------------------------------------**/

public OnCodeInit()
{
	P:1("Malloc_OnCodeInit called");
	if (heapspace() < MALLOC_MEMORY + 4 * 1024)
	{
		P:E("heapspace too low for y_malloc: Did you use \"#pragma dynamic\"?");
	}
	new
		Opcode:bounds = RelocateOpcode(OP_BOUNDS),
		Opcode:nop = RelocateOpcode(OP_NOP);
	for (new i = AMX_HEADER_COD, end = AMX_HEADER_DAT - 4; i < end; i += 4)
	{
		// Make sure this isn't just something that LOOKS like "bounds 0",
		// although I don't think there can be because "0" is not a valid
		// opcode.
		if (AMX_Read(i) == _:bounds && AMX_Read(i + 4) == 0)
		{
			// Found a bounds code.
			AMX_Write(i, _:nop);
			i += 4;
			AMX_Write(i, _:nop);
		}
	}
	// Run all other code setup first (most notably, y_hooks setup).
	#if defined Malloc_OnCodeInit
		Malloc_OnCodeInit();
	#endif
	// Check the heap base, to ensure nothing is currently allocated.
	new heap;
	// Should also be the same as `LCTRL 2`, but no need for a third comparison.
	#emit HEAP         0
	#emit STOR.S.alt   heap
	if (heap != AMX_HEADER_HEA)
	{
		// Some heap allocation ocurred somewhere in this call chain and hasn't
		// been freed yet.
		P:F("Unexpected heap allocations in y_malloc.  Try changing include orders");
	}
	{}
	// Allocate the heap space initially.
	heap = MALLOC_MEMORY * 4;
	P:6("Malloc_OnCodeInit: allocate %d", heap);
	#emit LCTRL        2
	#emit LOAD.S.alt   heap
	#emit ADD
	#emit SCTRL        2
	// Get the offset to the heap relative to the access var `YSI_gMallocMemory`.
	#emit CONST.alt    YSI_gMallocMemory
	#emit LOAD.pri     AMX_HEADER_HEA
	#emit SUB
	#emit SHR.C.pri    2 // Divide by 4 to get cells.
	#emit STOR.pri     __YSI_g_sHeapStart
	#emit INC.pri
	#emit STOR.pri     __YSI_g_sUnusedStart
	// Initialise the linked lists, now we have code access.
	YSI_gMallocMemory[YSI_g_sHeapStart] = MALLOC_MEMORY - 1;
	YSI_gMallocMemory[YSI_g_sUnusedStart] = 0;
	// Write something to the original array location (so it is used at least).
	YSI_gMallocMemory[0] = MALLOC_MEMORY;
	#if _DEBUG > 4
		// The "#if" is actually ignored by these "#emit" codes, as always.
		#emit CONST.alt    YSI_gMallocMemory
		#emit STOR.S.alt   heap
		printf("Malloc_OnCodeInit: AMX_HEADER_HEA = %d, YSI_gMallocMemory = %d, YSI_g_sHeapStart = %d", _:AMX_HEADER_HEA, heap, YSI_g_sHeapStart);
		printf("Malloc_OnCodeInit: YSI_gMallocMemory + 4 * YSI_g_sHeapStart = %d", heap + 4 * YSI_g_sHeapStart);
	#endif
	// Loop through all the exposed public functions.
	new
		idx = 0,
		entry,
		addr,
		ctx[AsmContext];
	CGen_UseCodeSpace(ctx);
	// Get the pointer to `main` as well - don't forget that one!
	#emit LCTRL                     1
	#emit STOR.S.pri                addr
	entry = -addr + 28;
	P:6("Malloc_OnCodeInit: main = %d", entry);
	new offset = GetAmxBaseAddress() + AMX_HEADER_COD - AMX_BASE_ADDRESS;
	do
	{
		addr = AMX_Read(entry);
		P:7("Malloc_OnCodeInit: addr = %08x, new = %08x", addr, ctx[AsmContext_buffer] + ctx[AsmContext_buffer_offset] - AMX_HEADER_COD);
		// Move the pointer in the header to our stub.
		AMX_Write(entry, ctx[AsmContext_buffer] + ctx[AsmContext_buffer_offset] - AMX_HEADER_COD);
		// Check if the heap has already been modified in the current stack.
		@emit HEAP         0                                    // Get heap location in `alt`.
		@emit CONST.pri    (AMX_HEADER_HEA + MALLOC_MEMORY * 4) // Get the end of malloc data.
		@emit JSLEQ        addr + offset                        // Already allocated.
		@emit SCTRL        2                                    // Store the new end.
		@emit JUMP         addr + offset                        // Continue with code.
	}
	while ((idx = AMX_GetPublicEntry(idx, entry)));
	// Allocate memory for callback parameters to use.  They use some of the heap when passing
	// strings etc, so save some space at the bottom of the heap for them to use.  This just leaks
	// memory from the allocation system, and allows it to be safely clobbered by those calls.
	Malloc_Allocate(YSI_DEFAULT_MALLOC);
	CGen_AddCodeSpace(AsmGetCodeSize(ctx));
	P:6("Malloc_OnCodeInit done");
	return 1;
}

#undef OnCodeInit
#define OnCodeInit Malloc_OnCodeInit
#if defined Malloc_OnCodeInit
	forward Malloc_OnCodeInit();
#endif

