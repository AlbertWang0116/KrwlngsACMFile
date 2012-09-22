
//My own way to solve congruence equation kx=z(mod y)[x,z < y], based on the modular arithmetic. The result is the least positive answer of the equation.
//if the range of x, y, z is out of the int, the answer may also be out of range, then use long long instead.
//the largest value in process of arithmetic can be up to y^2, see the part of converting to long long.
int mygcd(int x, int y, int z) {
	int ret;
	if (!(z%x)) return z/x; if (x == y) return -1;
	ret = mygcd(x-y%x, x, z%x);
	if (ret<0) return -1; return ((long long)y*ret+z) / x;
}

int myoclean(int x, int y, int z) {
	if (!x) if (!z) return 0; else return -1;
	return mygcd(x, y, z);
}

//Standard way to solve congruence equation kx=z(mod y)[x,z < y], based on extended oclidean algorithm.
//The result of code below is the least positive answer of the equation. If there's no need to calculate that, ans can be [(z/ret)*k1]+I*(y/ret), I is any integer.
//the largest value in process of arithmetic can be up to y*z, see the part of converting to long long.
int k1, k2;
int extgcd(int x, int y) {
	int ret, tmp;
	if (!y) { k1 = 1; k2 = 0; return x; }
	ret = extgcd(y, x%y);
	tmp = k1-x/y*k2; k1 = k2; k2 = tmp; return ret;
}

int extoclean(int x, int y, int z) {
	int ret = extgcd(x, y); int ans;
	if (z%ret) return -1;
	ans = ((long long)(z/ret)*k1%(y/ret));
	if (ans < 0) ans += y/ret; return ans;
}
