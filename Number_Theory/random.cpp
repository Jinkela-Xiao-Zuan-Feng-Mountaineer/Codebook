inline int random_int(){
	static int seed=20160424;
	return seed+=(seed<<16)+0x1db3d743;
}
inline long long random_long_long(){
	static long long seed=20160424;
	return seed+=(seed<<32)+0xdb3d742c265539d;
}
