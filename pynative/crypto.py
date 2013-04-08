"""A python native implementation of the public key crypto in Cube 2
Based on the Sauerbraten Sources and https://github.com/mgaare/cube2-crypto
"""

from Crypto import Random
import operator

P = object()
B = object()
base = object()
x = object()
y = object()
z = object()
origin = object()

ecc_params = {P: 0xfffffffffffffffffffffffffffffffeffffffffffffffff,
              B: 0x64210519e59c80e70fa7e9ab72243049feb8deecc146b9b1,
              base: (0x188da80eb03090f67cbf20eb43a18800f4ff0afd82ff1012,
                     0x07192b95ffc8da78631011ed6b24cdd573f977a11e794811,
                     0x000000000000000000000000000000000000000000000001),
              origin: {x: 1, y: 1, z: 0}}
              
def get_random_number(bits):
    return int("".join(map(lambda b: hex(ord(b))[2:], Random.get_random_bytes(bits))), 16)

def bit_test(num, bit):
    return num & (0x1 << bit) != 0

def extended_euclidean_gcd(a, b):
    """Copied from
    http://en.wikibooks.org/wiki/Algorithm_Implementation/Mathematics/Extended_Euclidean_algorithm"""
    x,y, u,v = 0,1, 1,0
    while a != 0:
        q,r = b//a,b%a; m,n = x-u*q,y-v*q
        b,a, x,y, u,v = a,r, u,v, m,n
    return b, x, y

def modular_inverse(a, m):
    "Copied from same source as euclidean gcd"
    g, x, y = extended_euclidean_gcd(a, m)
    if g != 1:
        return None  # modular inverse does not exist
    else:
        return x % m

def with_modulus(m, f):
    return lambda *args: f(*args) % m

def with_ecc_params(params):
    return lambda f: with_modulus(params[P], f)

params_f = with_ecc_params(ecc_params)

m_add = params_f(operator.add)
m_dbl = lambda x: m_add(x, x)
m_sub = params_f(operator.sub)
m_mul = params_f(operator.mul)
m_sqr = lambda x: m_mul(x, x)
m_pow = params_f(operator.pow)
m_div = params_f(operator.div)

def m_div2(x, y):
    #if(hasbit(0)) { gfint::add(x, P); rshift(1); }
    if bit_test(y, 0):
        x = y + ecc_params[P]
        x = x>>1
    #else rshift(x, 1);
    else:
        x = y>>1
    
    #return *this;
    return x
                
def big_m_pow(x, exp, carry=None):
    if carry is None:
        if bit_test(exp, 0):
            carry = x
        else:
            carry = 1
    else:
        if exp == 0:
            return carry
        else:
            x = m_sqr(x)
            if bit_test(exp, 0):
                carry = m_mul(carry, x)
    return big_m_pow(x, exp>>1, carry)

def jacobian_add(S, Q):
    x, y, z = S
    qx, qy, qz = Q

    #if(q.z.iszero()) return;
    if qz == 0:
        return S
    
    #else if(z.iszero()) { *this = q; return; }
    elif z == 0:
        return Q
    
    #gfield a, b, c, d, e, f;
    a, b, c, d, e, f = 0,0,0,0,0,0
    
    #a.square(z);
    a = m_sqr(z)
    
    #b.mul(q.y, a).mul(z);
    b = m_mul(m_mul(qy, a), z)
    
    #a.mul(q.x);
    a = m_mul(a, qx)
    
    #if(q.z.isone())
    #{
    #    c.add(x, a);
    #    d.add(y, b);
    #    a.sub(x, a);
    #    b.sub(y, b);
    #}
    if qz == 1:
        #print "qz == 1 is True"
        c = m_add(x, a)
        d = m_add(y, b)
        a = m_sub(x, a)
        b = m_sub(y, b)
    
    #else
    #{
    #    f.mul(y, e.square(q.z)).mul(q.z);
    #    e.mul(x);
    #    c.add(e, a);
    #    d.add(f, b);
    #    a.sub(e, a);
    #    b.sub(f, b);
    #}
    else:
        #print "qz == 1 is False"
        e = m_sqr(qz)
        f = m_mul(y, e)
        f = m_mul(f, qz)
        
        e = m_mul(e, x)
        c = m_add(e, a)
        d = m_add(f, b)
        a = m_sub(e, a)
        b = m_sub(f, b)
    
    #if(a.iszero()) { if(b.iszero()) mul2(); else *this = origin; return; }
    if a == 0:
        if b == 0:
            return jacobian_double(x, y, z)
        else:
            return (1, 1, 0)
    
    #if(!q.z.isone()) z.mul(q.z);
    if qz != 1:
        z = m_mul(z, qz)
    
    #z.mul(a);
    z = m_mul(z, a)
    
    #x.square(b).sub(f.mul(c, e.square(a)));
    e = m_sqr(a)
    f = m_mul(c, e)
    x = m_sqr(b)
    x = m_sub(x, f)
    
    #y.sub(f, x).sub(x).mul(b).sub(e.mul(a).mul(d)).div2();
    e = m_mul(e, a)
    e = m_mul(e, d)
    
    y = m_sub(f, x)
    y = m_sub(y, x)
    y = m_mul(y, b)
    y = m_sub(y, e)
    
    y = m_div2(y, y)
    
    return (x, y, z)

def legendre(x, P):
    res = big_m_pow(x, (P-1)/2)
    if res == 0:
        return 0
    elif res == 1:
        return 1
    else:
        return -1

def legendre_sqrt(x, P):
    check = legendre(x, P)
    if check == 0:
        return 0
    elif check == -1:
        return None
    elif check == 1:
        return big_m_pow(x, (P+1)/4)

def jacobian_double(x, y, z):
    
    if z == 0:
        return (x, y, z)
    elif y == 0:
        return ecc_params[origin]
    a, b, c, d = 0,0,0,0
    
    #d.sub(x, c.square(z));
    c = m_sqr(z)
    d = m_sub(x, c)
    
    #d.mul(c.add(x));
    c = m_add(c, x)
    d = m_mul(d, c)
    
    #c.mul2(d).add(d);
    c = m_add(m_dbl(d), d)
    
    #z.mul(y).add(z);
    z = m_mul(z, y)
    z = m_add(z, z)
    
    #a.square(y);
    a = m_sqr(y)

    #b.mul2(a);
    b = m_dbl(a)
    
    #d.mul2(x).mul(b);
    d = m_mul(m_dbl(x), b)
    
    #x.square(c).sub(d).sub(d);
    x = m_sub(m_sub(m_sqr(c), d), d)
    
    #a.square(b).add(a);
    #a = m_add(m_sqr(b), a)
    a = m_sqr(b)
    a = m_add(a, a)
    
    #y.sub(d, x).mul(c).sub(a);
    #y = m_sub(m_mul(m_sub(d, x), c), a)
    y = m_sub(d, x)
    y = m_mul(y, c)
    y = m_sub(y, a)
    
    return (x, y, z)

def numbits(n):
    if n >= 0:
        return len(bin(n))-2
    else:
        return len(bin(n))-3

def jacobian_mult(p, n):
    this = (1, 1, 0)
    for i in xrange(numbits(n)-1,-1,-1):
        this = jacobian_double(*this)
        if bit_test(n, i):
            this = jacobian_add(this, p)
    return this

def jacobian_normalize(x, y, z):
    if z in (0, 1):
        return (x, y, z)
    
    z = modular_inverse(z, ecc_params[P])
    tmp = m_sqr(z)
    x = m_mul(x, tmp)
    y = m_mul(y, tmp)
    y = m_mul(y, z)
    z = 1
    return (x, y, z)
    
def parse_jacobian(s):
    ybit, s = s[0] == '-', s[1:]
    x = int(s, 16)
    
    tmp = m_add(m_dbl(x), x)
    #y2 = m_add(m_sub(m_mul(m_sqr(x), x), tmp), ecc_params[B])
    y2 = m_add(m_sub(m_pow(x, 3), m_mul(x, 3)), ecc_params[B])
    y = legendre_sqrt(y2, ecc_params[P])
    if y is None:
        y = 0
    if bit_test(y, 0) != ybit:
        y = -y
    
    z = 1
    
    return (x, y, z)
    
def jacobian_to_str(x, y, z):
    if bit_test(y, 0):
        sign = '-'
    else:
        sign = '+'
        
    return sign+hex(x)[2:-1]

def get_public_key(privkeystr):
    privkey = int(privkeystr, 16)
    c = jacobian_mult(ecc_params[base], privkey)
    p = jacobian_normalize(*c)
    pubkey = jacobian_to_str(*p)
    return pubkey
    
def generate_key_pair():
    privkey = get_random_number(24)
    privkeystr = hex(privkey)[2:-1]
    pubkeystr = get_public_key(privkeystr)
    return (privkeystr, pubkeystr)

def answer_challenge(privkeystr, challengestr):
    privkey = int(privkeystr, 16)
    answer = parse_jacobian(challengestr)
    answer = jacobian_mult(answer, privkey)
    x, y, z = jacobian_normalize(*answer)
    return hex(x)[2:-1].zfill(48)

def generate_challenge(pubkeystr):
    pubkey = parse_jacobian(pubkeystr)
    challenge = get_random_number(24)
    
    answer = jacobian_mult(pubkey, challenge)
    answer = jacobian_normalize(*answer)
    
    secret = jacobian_mult(ecc_params[base], challenge)
    secret = jacobian_normalize(*secret)
    
    challengestr = jacobian_to_str(*secret)
    answerstr = hex(answer[0])[2:-1].zfill(48)
    
    return (challengestr, answerstr)

if __name__ == '__main__':
    authkeys = [
        {'private': 'f373de2d49584e7a16166e76b1bb925f24f0130c63ac9332', 'public': '+2c1fb1dd4f2a7b9d81320497c64983e92cda412ed50f33aa'},
        {'private': '0978245f7f243e61fca787f53bf9c82eabf87e2eeffbbe77', 'public': '-afe5929327bd76371626cce7585006067603daf76f09c27e'},
        {'private': '935f7b951c132951527ab541ffc5b8bff258c1e88414ab2a', 'public': '-d954ee56eddf2b71e206e67d48aaf4afe1cc70f8ca9d1058'},
        {'private': 'f6295aa51aca7f511c441e754830cf0d951a2078cbf881d9', 'public': '-454c98466c45fce242724e6e989bdd9f841304a1fcba4787'},
        {'private': 'e9ee7bf32f60110b2a0355ccbf120404307de5ee72a41417', 'public': '+15fda493cb1095ca40f652b0d208769bd42b9e234e48d1a8'},
        {'private': '8ef7537b1e631ca7c30a4fe8f70d61b7f2589c9ba1f97b0f', 'public': '+643d99cb21178557f4e965eb6dc1ec1e4f57b3b05375fafb'},
    ]
    
    import unittest
    import cube2crypto

    class TestCube2Crypto(unittest.TestCase):
        def test_public_key_recovery(self):
            for authkey in authkeys:
                self.assertEqual(authkey['public'], get_public_key(authkey['private']))
                
        def test_challenges_native_to_py(self):
            for authkey in authkeys:
                generated_challenge = cube2crypto.genchallenge(authkey['public'], Random.get_random_bytes(24))
                answer = answer_challenge(authkey['private'], generated_challenge[0])
                
                self.assertEqual(generated_challenge[1], answer)

        def test_challenges_py_to_native(self):
            for authkey in authkeys:
                generated_challenge = generate_challenge(authkey['public'])
                answer = cube2crypto.answerchallenge(authkey['private'], generated_challenge[0])
                
                self.assertEqual(generated_challenge[1], answer)

    suite = unittest.TestLoader().loadTestsFromTestCase(TestCube2Crypto)
    unittest.TextTestRunner(verbosity=2).run(suite)

