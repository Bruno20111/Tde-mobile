#define Y_UTILS_NO_VALUE
#define Y_UTILS_VALUE (42)
#define Y_UTILS_INVALID (999999)

TEST_COMPILE__ y_utils()
{
#if __COMPILER_2ND_PASS
	#assert NO_VALUE(Y_UTILS_NO_VALUE)
	#assert !NO_VALUE(Y_UTILS_VALUE)
	#assert IS_IN_RANGE(Y_UTILS_VALUE, -30, 43)
	#assert !IS_IN_RANGE(Y_UTILS_VALUE, -30, 42)
	#assert NOT_IN_RANGE(Y_UTILS_VALUE, 0, 10)
	#assert !NOT_IN_RANGE(Y_UTILS_VALUE, 20, 100)
	#assert VALID_PLAYERID(Y_UTILS_VALUE)
	#assert !VALID_PLAYERID(Y_UTILS_INVALID)
	#assert UCMP(4, 100)
	#assert !UCMP(-4, 100)
	BeautifyProfilingTime(0, 0);
	#assert ceildiv(12, 3) == 4
	#assert ceildiv(11, 3) == 4
	#assert ceildiv(10, 3) == 4
	#assert ceildiv(9, 3) == 3
	#assert ceildiv(8, 3) == 3
	#assert floordiv(12, 3) == 4
	#assert floordiv(11, 3) == 3
	#assert floordiv(10, 3) == 3
	#assert floordiv(9, 3) == 3
	#assert floordiv(8, 3) == 2
	#assert IsOdd(3)
	#assert !IsOdd(8)
	#assert IsEven(8)
	#assert !IsEven(3)
#endif
	new str[32];
	ASSERT(IsNull(str));
	StrToLower(str);
	StrToUpper(str);
	Random(0);
	RandomFloat(0.0);
	StripNL(str);
	StripR(str);
	StripL(str);
	Strip(str);
	EndOfLine(str, 0);
	ChrFind(' ', str);
	// Gives a deprecation warning.  That's fine (for tests).
	chrfindp(' ', str);
	IPToInt(str);
	// Gives a deprecation warning.  That's fine (for tests).
	bernstein(str);
	IsHex(str);
	Unpack(str);
	#if defined _samp_included
		ASSERT_ZE(GetIP(0));
	#endif
	ReturnStringArg(0);
	va_return(str);
	IsNumeric(str);
}

static stock
	gCalls_y_utils_va_return = 0;

forward y_utils_va_return(const str[]);

public y_utils_va_return(const str[])
{
	ASSERT_SAME(str, "Hello World 42 9.455");
	++gCalls_y_utils_va_return;
}

TEST__ y_utils_va_return()
{
	gCalls_y_utils_va_return = 0;
	y_utils_va_return(va_return("Hello %s %d %.3f", "World", 42, 9.4554));
	R@("y_utils_va_return", "s", va_return("Hello %s %d %.3f", "World", 42, 9.4554));
	R@(va_return("%s_%s", "y_utils", "va_return"), "s", "Hello World 42 9.455");
	R@(va_return("%s_%s", "y_utils", "va_return"), va_return("s"), va_return("Hello %s %d %.3f", "World", 42, 9.4554));
	ASSERT_EQ(gCalls_y_utils_va_return, 4);
}

TEST__ y_utils_LevenshteinDistance()
{
	ASSERT_EQ(LevenshteinDistance("hello", "hello"), 0);
	ASSERT_EQ(LevenshteinDistance("Hello", "hello"), 1);
	ASSERT_EQ(LevenshteinDistance("helllo", "hello"), 1);
	ASSERT_EQ(LevenshteinDistance("helo", "hello"), 1);
	ASSERT_EQ(LevenshteinDistance("hellllo", "hello"), 2);
	ASSERT_EQ(LevenshteinDistance("heo", "hello"), 2);
	ASSERT_EQ(LevenshteinDistance("he,,o", "hello"), 2);
	ASSERT_EQ(LevenshteinDistance("HhlTo", "hello"), 3);
	ASSERT_EQ(LevenshteinDistance("hello", "there"), 4);
	ASSERT_EQ(LevenshteinDistance("hello", ""), 5);
	ASSERT_EQ(LevenshteinDistance("", "hello"), 5);
	ASSERT_EQ(LevenshteinDistance("", "01234567890123456789012345678901234567890123456789012345678901234567890123456789"), 80);
	ASSERT_EQ(LevenshteinDistance("01234567890123456789012345678901234567890123456789012345678901234567890123456789", "01234567890123456789012345678901234567890123456789012345678901234567890123456789"), 0);
	ASSERT_EQ(LevenshteinDistance("aa", "01234567890123456789012345678901"), 32);
	// Error case.
	ASSERT_EQ(LevenshteinDistance("0123456789012345678901234567890123456789", "01234567890123456789012345678901234567890123456789012345678901234567890123456789"), 1);
}

